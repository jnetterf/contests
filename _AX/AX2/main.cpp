#include <QtGui/QApplication>
#include "mainwindow.h"
#include "tablecolumn.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    TableColumn tc;
    tc.show();

    return a.exec();
}
