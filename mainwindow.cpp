#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(20);

    setFixedSize(WIDTH, HEIGHT);

    playerPaddle = new Paddle();
    playerPaddle->leftBorder = 0;
    playerPaddle->rightBorder = WIDTH;
    // !!!setting border must be before setting position!!!
    playerPaddle->setPosition(QPoint(0, HEIGHT - Paddle::HEIGHT));

    computerPaddle = new Paddle();
    computerPaddle->leftBorder = 0;
    computerPaddle->rightBorder = WIDTH;
    computerPaddle->setPosition(QPoint(0, 0));


    ball = new Ball();
    ball->leftBorder = 0;
    ball->rightBorder = WIDTH;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePlayerX(float x)
{
    auto p = playerPaddle->getPosition();
    playerPaddle->setPosition({x * width(), p.y()});
}

void MainWindow::nextFrame(){
    playerPaddle->update();
    playerPaddle->updateSpeeedFromHandRects(handRects);
    PaddleAI::movePaddle(computerPaddle, ball);
    computerPaddle->update();
    if(ball->checkCollisionWithBottomPaddle(playerPaddle)){
        ball->changeSpeedAfterCollisionWithPaddle();
        ball->updateAfterCollisionWithPaddle(playerPaddle);
    }
    if(ball->checkCollisionWithTopPaddle(computerPaddle)){
        ball->changeSpeedAfterCollisionWithPaddle();
        ball->updateAfterCollisionWithPaddle(computerPaddle);
    }
    ball->update();

    if(checkForTopPoint()){
        topPlayerPoints++;
        reset();
    }
    if(checkForBottomPoint()){
        bottomPlayerPoints++;
        reset();
    }

//    qDebug() << ball->getXSpeed() << " " << ball->getYSpeed();
    update();
}


void MainWindow::reset(){
    playerPaddle->setPosition(QPoint(0, HEIGHT - Paddle::HEIGHT));
    playerPaddle->setSpeed(Paddle::INITIAL_SPEED);
    computerPaddle->setPosition(QPoint(0, 0));
    computerPaddle->setSpeed(Paddle::INITIAL_SPEED);
    ball->setPosition(QPoint(200, 200));
    ball->setYSpeed(Ball::INITIAL_YSPEED);
    ball->setXSpeed(Ball::INITIAL_XSPEED);
}


bool MainWindow::checkForBottomPoint(){
    return ball->getPosition().y() >= HEIGHT - Paddle::HEIGHT;
}

bool MainWindow::checkForTopPoint(){
    return ball->getPosition().y() <= Paddle::HEIGHT;
}


void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    playerPaddle->draw(&painter);
    computerPaddle->draw(&painter);
    ball->draw(&painter);
//    qDebug() << currentHandRects;
}



void MainWindow::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_A){
        playerPaddle->setSpeed(-std::abs(playerPaddle->getSpeed()));
    }
    if(event->key() == Qt::Key_D){
        playerPaddle->setSpeed(std::abs(playerPaddle->getSpeed()));
    }
}





void MainWindow::setHandRects(const QVector<QRect> &rects){
    handRects = rects;
}
