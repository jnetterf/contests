#include <QLocalSocket>
#ifndef CLIENT_H
#define CLIENT_H

class Client
{
public:
    QLocalSocket ls;
    Client();
};

#endif // CLIENT_H
