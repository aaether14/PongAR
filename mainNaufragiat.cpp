#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>

struct QPairFirstComparer
{
    template<typename T1, typename T2>
    bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
    {
        return a.first >= b.first;
    }
};

struct QPairSecondComparer
{
    template<typename T1, typename T2>
    bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
    {
        return a.second >= b.second;
    }
};


int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 //scriere
 QString newName = "player";

 QString newScore = QString::number(500);

 QString filename="/home/andrei/Documents/facultate/an 3/sem 2/Ingineria Programării/HelloWorld/input.txt";
 QFile file( filename );
 if ( file.open(QIODevice::Append) )
 {
     QTextStream stream( &file );
     stream << newName << endl << newScore << endl;
 }
 file.close();

 QWidget window;
 window.setFixedSize(500, 500);

 QLabel *title = new QLabel("HIGHSCORES", &window);
 title->setGeometry(100, 10, 110, 30);

 // citire
 QFile inputFile("/home/andrei/Documents/facultate/an 3/sem 2/Ingineria Programării/HelloWorld/input.txt");

 QList<QPair<QString,int> > array;
 if (inputFile.open(QIODevice::ReadOnly))
 {
     QTextStream in(&inputFile);
     while (!in.atEnd())
     {
         QString name = in.readLine();
         QString score = in.readLine();
         array.append(qMakePair(name,score.toInt()));
     }
     inputFile.close();
 }

 qSort(array.begin(), array.end(), QPairSecondComparer());
 //------------------------------end test
 int l = 1;
 for( int i=0; i<array.count(); ++i )
 {
     l++;
     QString name = array[i].first;
     int score = array[i].second;
     QLabel *labelName = new QLabel(name, &window);
     QLabel *labelScore = new QLabel(QString::number(score) , &window);
     labelName->setGeometry(10, 20 * l, 110, 30);
     labelScore->setGeometry(200, 20 * l, 110, 30);
 }

 window.show();
 return app.exec();
}
