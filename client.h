#pragma once

#include <QMainWindow>
#include "mainwindow.h"
#include "imageutils.h"

namespace Ui 
{
    class ClientMainWindow;
}

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QWidget* parent = nullptr);
    virtual ~ClientMainWindow() override;

private:
    Ui::ClientMainWindow* ui = nullptr;
    class QCamera* m_camera = nullptr;
    class QVBoxLayout* m_verticalLayout = nullptr;
    class CameraFrameGrabber* m_cameraFrameGrabber = nullptr;

private slots:
    void onNewFrame(const QImage& image);

public:
    MainWindow* mainWindow;
    bool m_isSamplingForCalibration = false;
    std::vector<cv::Mat> m_calibrationSampleFrames = {};
    cv::Mat m_handHistogram = {};
    cv::Ptr<cv::BackgroundSubtractor> m_backgroundSubstractor = {};

protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

};
