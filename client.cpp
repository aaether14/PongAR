#include "client.h"
#include "ui_client.h"
#include "cameraframegrabber.h"

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>


ClientMainWindow::ClientMainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow()),
    m_camera(new QCamera(this)),
    m_cameraFrameGrabber(new CameraFrameGrabber(this))
{
    ui->setupUi(this);
    connect(m_cameraFrameGrabber, &CameraFrameGrabber::frameAvailable, this, &ClientMainWindow::onNewFrame);
    m_camera->setViewfinder(m_cameraFrameGrabber);
    m_camera->start();
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}

void ClientMainWindow::onNewFrame(const QImage& image)
{
    if (m_isSamplingForCalibration) {
            auto cr = ui->mainCameraHandler->calibrationRect();
            cv::Mat calibrationSampleFrame = QImageToMat(image.copy({cr.x() * image.width(), cr.y() * 
                image.height(), cr.width() * image.width(), cr.height() * image.height()}));
            cv::cvtColor(calibrationSampleFrame, calibrationSampleFrame, cv::COLOR_RGB2HSV);
            m_calibrationSampleFrames.push_back(calibrationSampleFrame);
    }
    if (!m_handHistogram.empty()) {
        cv::Mat cvFrame = QImageToMat(image);
        cv::Mat hsvFrame;
        cv::cvtColor(cvFrame, hsvFrame, cv::COLOR_RGB2HSV);
        cv::Mat maskedFrame = histogramMasking(hsvFrame, m_handHistogram);
        ui->mainCameraHandler->setImage(cvMatToQImage(maskedFrame));
    }
    else {
        ui->mainCameraHandler->setImage(image);
    }
}

void ClientMainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
        qDebug() << "Started calibration.";
        m_calibrationSampleFrames.clear();
        m_isSamplingForCalibration = true;
    }
}

void ClientMainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
        qDebug() << "Calibration ended.";
        m_isSamplingForCalibration = false;
        if (!m_calibrationSampleFrames.empty()) {
            m_handHistogram = computeHandHistogram(m_calibrationSampleFrames);
        }
    }
}
