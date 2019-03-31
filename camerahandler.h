#pragma once

#include <QWidget>
#include <QPixmap>

class CameraHandler : public QWidget
{
    Q_OBJECT

public:
    explicit CameraHandler(QWidget* parent = nullptr);
    virtual ~CameraHandler() override;

    void setPixmap(const QPixmap& pixmap);
    const QPixmap& pixmap() const;

    void setHandRects(const QVector<QRect>& handRects);

private:
    QPixmap m_pixmap;
    QVector<QRect> m_handRects;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};