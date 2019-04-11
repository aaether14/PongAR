#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QPoint>
#include "paddle.h"
#include <math.h>

class Ball
{
public:
    static const int RADIUS = 10;
    int leftBorder;
    int rightBorder;
    static const int INITIAL_XSPEED = 1;
    static const int INITIAL_YSPEED = 5;

    Ball();

    void draw(QPainter* painter);
    void update();

    bool checkCollisionWithBottomPaddle(Paddle* paddle);
    bool checkCollisionWithTopPaddle(Paddle* paddle);
    void changeSpeedAfterCollisionWithPaddle();

    int getCollisionXCoordinate(Paddle* paddle);

    void updateAfterCollisionWithPaddle(Paddle* paddle);

    QPoint getPosition();
    void setPosition(const QPoint& p);
    void setYSpeed(int s);
    void setXSpeed(int s);
    int getYSpeed();
    int getXSpeed();

    int clampXSpeed(int s);

private:
    int xspeed;
    int yspeed;
    QPoint position;

    //TO DO: add other movement parameters


};

#endif // BALL_H
