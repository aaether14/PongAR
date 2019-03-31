#include "camerahandler.h"

#include <QPainter>

CameraHandler::CameraHandler(QWidget* parent) : 
    QWidget(parent)
{
}

CameraHandler::~CameraHandler()
{
}

void CameraHandler::setHandRects(const QVector<QRect>& handRects)
{
    m_handRects = handRects;
}

void CameraHandler::setImage(const QImage& image)
{
    m_image = image;
    update();
}

const QImage& CameraHandler::image() const
{
    return m_image;
}

void CameraHandler::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawImage(rect(), m_image);
    painter.drawRects(m_handRects);
}