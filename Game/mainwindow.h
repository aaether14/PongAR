#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include "paddle.h"
#include "ball.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void nextFrame();

private:
    const int WIDTH = 600;
    const int HEIGHT = 600;

    Ui::MainWindow *ui;
    QTimer* timer;
    int x = 0;

    Paddle* playerPaddle;
    Paddle* computerPaddle;
    Ball* ball;

    bool checkForTopPoint();
    bool checkForBottomPoint();
    void reset();

    int topPlayerPoints = 0;
    int bottomPlayerPoints = 0;

};

#endif // MAINWINDOW_H
