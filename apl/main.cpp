#include "mainwindow.h"

#include <QApplication>
#include <windows.h>


int main(int argc, char *argv[])
{
    //int x = 3, y = 4, z = 0;
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //return 0;
}
