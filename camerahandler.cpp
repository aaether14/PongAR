#include "camerahandler.h"

#include <QPainter>
#include <QDebug>

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

const QRectF CameraHandler::calibrationRect() const
{
    return {0.6, 0.2, 0.12, 0.20};
}

void CameraHandler::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawImage(rect(), m_image);
    painter.drawRects(m_handRects);
    auto cr = calibrationRect();
    painter.setPen(QPen(Qt::red, 3));
    painter.drawRect(QRectF{cr.x() * width(), cr.y() * height(), cr.width() * width(), cr.height() * height()});
}
