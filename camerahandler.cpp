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

void CameraHandler::setPixmap(const QPixmap& pixmap)
{
    m_pixmap = pixmap;
    update();
}

const QPixmap& CameraHandler::pixmap() const
{
    return m_pixmap;
}

void CameraHandler::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawPixmap(rect(), m_pixmap);
    painter.drawRects(m_handRects);
}