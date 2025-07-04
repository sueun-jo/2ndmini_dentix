#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QTcpServer>
#include <QJsonObject>

class Server; //포인터 사용하고 싶어용

class RequestDispatcher
{
public:
    static void handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server);
    static void handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server);

    //void handleChat();
};

#endif // REQUESTDISPATCHER_H
