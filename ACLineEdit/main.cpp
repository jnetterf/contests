#include <QtGui/QApplication>
#include "ACLineEdit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ACLineEdit w;
    w.show();

    return a.exec();
}
