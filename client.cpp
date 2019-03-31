#include "client.h"
#include "ui_client.h"
#include "cameraframegrabber.h"
#include "imageutils.h"

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

ClientMainWindow::ClientMainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow()),
    m_camera(new QCamera(this)),
    m_cameraFrameGrabber(new CameraFrameGrabber(this)),
    m_cascadeClassifier("fist.xml")
{
    ui->setupUi(this);
    connect(m_cameraFrameGrabber, &CameraFrameGrabber::frameAvailable, [this](const QImage& image){
        ui->mainCameraHandler->setPixmap(QPixmap::fromImage(image));
        cv::Mat cvImage = QImageToMat(image);
        std::vector<cv::Rect> handPositions = detectHand(cvImage, m_cascadeClassifier);
        QVector<QRect> handRects;
        for (auto& r : handPositions) {
            handRects << cvRectToQRect(r);
        }
        ui->mainCameraHandler->setHandRects(handRects);
    });
    m_camera->setViewfinder(m_cameraFrameGrabber);
    m_camera->start();
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}