/* a weekend project */

#include <QtGui/QApplication>
#include "imainwindow.h"
#include <QFile>
#include <QDebug>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f(":/style/styleSheet.txt");
    f.open(QFile::ReadOnly | QFile::Text);
    a.setStyleSheet(f.readAll());
    IMainWindow w;
    w.show();

    return a.exec();
}
