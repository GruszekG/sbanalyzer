#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    saveMeasurementsWindow s;
    s.show();
    //RealTimePlotWindow r;
    //r.show();
    //DialogWindow d;
    //d.show();
    return a.exec();
}
