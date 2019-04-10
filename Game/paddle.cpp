#include "paddle.h"

Paddle::Paddle()
{
    speed = -5;
    position = QPoint(0, 0);
}

void Paddle::draw(QPainter* painter){
    painter->drawRect(position.x(), position.y(), WIDTH, HEIGHT);
}


void Paddle::update(){
    setPosition(QPoint(getPosition().x() + speed, getPosition().y()));
}


void Paddle::setSpeed(int s){
    speed = s;
}

int Paddle::getSpeed(){
    return speed;
}

void Paddle::setPosition(const QPoint &p){
    if(p.x() < leftBorder || p.x() + WIDTH > rightBorder){
        return;
    }
    position = p;
}

QPoint Paddle::getPosition(){
    return position;
}
