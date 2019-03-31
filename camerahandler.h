#pragma once

#include <QWidget>

class CameraHandler : public QWidget
{
    Q_OBJECT

public:
    explicit CameraHandler(QWidget* parent = nullptr);
    virtual ~CameraHandler() override;

    void setImage(const QImage& image);
    const QImage& image() const;

    void setHandRects(const QVector<QRect>& handRects);

private:
    QImage m_image;
    QVector<QRect> m_handRects;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};