#include <QLocalServer>
#include <QObject>

#ifndef SERVER_H
#define SERVER_H

class Server : public QObject
{
    Q_OBJECT
public:
    QLocalServer _server;
    Server();
public slots:
    void magic();
};

#endif // SERVER_H
