#include "paddleai.h"

PaddleAI::PaddleAI()
{

}

void PaddleAI::movePaddle(Paddle* paddle, Ball* ball){
    //follow the direction of the ball
//    int xspeed = ball->getXSpeed();
//    if(xspeed > 0){
//        paddle->setSpeed(std::abs(paddle->getSpeed()));
//    }else{
//        paddle->setSpeed(-std::abs(paddle->getSpeed()));
//    }

    int ballPosition = ball->getPosition().x();
    int paddlePosition = paddle->getPosition().x();
    int paddleSpeed = paddle->getSpeed();
    if(std::abs((paddlePosition - paddleSpeed) - ballPosition) < std::abs((paddlePosition + paddleSpeed) - ballPosition)){
        paddle->setSpeed(-paddle->getSpeed());
    }
}
