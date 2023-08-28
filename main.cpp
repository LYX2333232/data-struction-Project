#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //应用程序a
    QApplication a(argc, argv);
    //主窗口w
    MainWindow w;
    w.show();

    return a.exec();
}
