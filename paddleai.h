#ifndef PADDLEAI_H
#define PADDLEAI_H

#include "paddle.h"
#include "ball.h"

class PaddleAI
{
public:
    PaddleAI();

    static void movePaddle(Paddle* paddle, Ball* ball);
};

#endif // PADDLEAI_H
