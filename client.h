#pragma once

#include <QMainWindow>
#include <opencv2/objdetect.hpp>

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
    cv::CascadeClassifier m_cascadeClassifier;
};