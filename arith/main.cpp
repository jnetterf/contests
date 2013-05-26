#include <QtGui/QApplication>
#include "arith.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arith w;
    w.show();

    return a.exec();
}
