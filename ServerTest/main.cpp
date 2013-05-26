#include <QtCore/QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QLocalSocket ls;
    ls.connectToServer("kstScript");
    qDebug()<<"Connected.";
    ls.waitForConnected(3000);
    QByteArray ba="commands()";
    ls.write(ba); ls.flush(); ls.waitForReadyRead(3000); qDebug()<<ls.read(30000);
     qDebug()<<ls.read(30000);
    ba="done()";
    ls.write(ba); ls.flush(); ls.waitForReadyRead(3000); qDebug()<<ls.read(30000);
    qDebug()<<"Disconnected.";

}
