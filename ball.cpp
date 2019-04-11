#include "ball.h"

Ball::Ball()
{
    position = QPoint(200, 200);
    xspeed = INITIAL_XSPEED;
    yspeed = INITIAL_YSPEED;
}


void Ball::draw(QPainter* painter){
    painter->drawEllipse(position, RADIUS, RADIUS);
}

void Ball::update(){
    if(position.x() - RADIUS <= leftBorder){
        xspeed = -xspeed;
    }
    if(position.x() + RADIUS >= rightBorder){
        xspeed = -xspeed;
    }
    position.setX(position.x() + xspeed);
    position.setY(position.y() + yspeed);
}


bool Ball::checkCollisionWithBottomPaddle(Paddle* paddle){
    QPoint paddlePosition = paddle->getPosition();
    return (position.x() >= paddlePosition.x() && position.x() <= paddlePosition.x() + Paddle::WIDTH)
        && (position.y() + RADIUS >= paddlePosition.y());
}


bool Ball::checkCollisionWithTopPaddle(Paddle* paddle){
    QPoint paddlePosition = paddle->getPosition();
    return (position.x() >= paddlePosition.x() && position.x() <= paddlePosition.x() + Paddle::WIDTH)
         &&(position.y() - RADIUS <= paddlePosition.y() + Paddle::HEIGHT);
}


void Ball::updateAfterCollisionWithPaddle(Paddle *paddle){
    int collisionXCoordinate = position.x();
    int paddleLeft = paddle->getPosition().x();
    int paddleMiddle = (paddleLeft + (paddleLeft + Paddle::WIDTH)) / 2;
    collisionXCoordinate = collisionXCoordinate - paddleMiddle;
    xspeed = clampXSpeed(xspeed + collisionXCoordinate);
}


int Ball::getCollisionXCoordinate(Paddle *paddle){
    return position.x();
}


void Ball::changeSpeedAfterCollisionWithPaddle(){
    yspeed = -yspeed;
}


int Ball::clampXSpeed(int s){
    if(s >= 0){
        return std::min(s, 5);
    }
    if(s < 0){
        return std::max(s, -5);
    }
}

void Ball::setPosition(const QPoint& p){
    position = p;
}

QPoint Ball::getPosition(){
    return position;
}

void Ball::setYSpeed(int s){
    yspeed = s;
}

void Ball::setXSpeed(int s){
    xspeed = s;
}

int Ball::getXSpeed(){
    return xspeed;
}

int Ball::getYSpeed(){
    return yspeed;
}
