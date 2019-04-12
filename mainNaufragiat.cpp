#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 QWidget window;
 window.setFixedSize(500, 500);

 /*QPushButton *button = new QPushButton("Hello World", &window);
 button->setGeometry(10, 10, 80, 30);*/

 QLabel *title = new QLabel("HIGHSCORES", &window);
 title->setGeometry(100, 10, 110, 30);

 // citire
 int l = 1;
 QFile inputFile("/home/andrei/Documents/facultate/an 3/sem 2/Ingineria Programării/HelloWorld/input.txt");
 if (inputFile.open(QIODevice::ReadOnly))
 {
    QTextStream in(&inputFile);
    while (!in.atEnd())
    {
       l++;
       QString name = in.readLine();
       QString score = in.readLine();
       QLabel *labelName = new QLabel(name, &window);
       QLabel *labelScore = new QLabel(score, &window);
       labelName->setGeometry(10, 20 * l, 110, 30);
       labelScore->setGeometry(200, 20 * l, 110, 30);
    }
    inputFile.close();
 }

 //scriere
 QString filename="/home/andrei/Documents/facultate/an 3/sem 2/Ingineria Programării/HelloWorld/input.txt";
 QFile file( filename );
 if ( file.open(QIODevice::Append) )
 {
     QTextStream stream( &file );
     stream << "user\n10" << endl;
 }
 file.close();

 window.show();
 return app.exec();
}
