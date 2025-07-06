#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QTcpServer>
#include <QJsonObject>

#include "usermanager.h"

class Server; //포인터 사용하고 싶어용

class RequestDispatcher
{
public:

    static void handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server, UserManager* userManager);
    static void handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager);
};

#endif // REQUESTDISPATCHER_H
