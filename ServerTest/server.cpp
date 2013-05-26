#include "server.h"
#include <QLocalSocket>
#include <QByteArray>
#include <QDebug>

Server::Server()
{
    _server.removeServer("test");
    _server.listen("test");
    connect(&_server,SIGNAL(newConnection()),this,SLOT(magic()));
}

void Server::magic() {
    while(_server.hasPendingConnections()) {
        QLocalSocket* s=_server.nextPendingConnection();
        s->waitForReadyRead(3000);
        qDebug()<<s->read(1000000);
    }
}
