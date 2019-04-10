#ifndef PADDLE_H
#define PADDLE_H

#include <QPainter>
#include <QPoint>

class Paddle
{
public:
    static const int WIDTH = 100;
    static const int HEIGHT = 20;
    int leftBorder;
    int rightBorder;

    Paddle();

    void draw(QPainter* painter);
    void update();

    int getSpeed();
    void setSpeed(int s);
    QPoint getPosition();
    void setPosition(const QPoint& p);

private:
    QPoint position;
    int speed;
};

#endif // PADDLE_H
