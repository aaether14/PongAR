#include "paddle.h"
#include <QDebug>
#include <QCursor>

Paddle::Paddle()
{
    speed = INITIAL_SPEED;
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


void Paddle::updateSpeeedFromHandRects(const QVector<QRect>& rects){
    if(rects.isEmpty()){
        setSpeed(0);
        return;
    }
    int mean = 0;
    for(int i = 0; i < rects.length(); i++){
        mean += rects[i].x();
    }
    mean /= rects.length();
    setSpeed(mean - position.x());

//USE THIS TO MOVE THE PADDLE WITH THE MOUSE. IT WORKS WELL

//    int p2 = QCursor::pos().x();
//    setSpeed(p2 - position.x());
//    qDebug() << p2 - position.x();

}
