#include <QApplication>
#include "client.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ClientMainWindow client;
    MainWindow w;
    client.mainWindow = &w;
    client.show();
    w.show();
    return app.exec();
}
