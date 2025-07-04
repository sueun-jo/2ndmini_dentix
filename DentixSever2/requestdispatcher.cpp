#include "requestdispatcher.h"
#include "server.h"



void RequestDispatcher::handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server){
    QString type = obj["type"].toString();
    QJsonObject data = obj["data"].toObject();

    if (type == "login"){
        handleLogin(socket, data, server);
    } else if (type == "chat"){
        //not yet implemented
    } else {
        QJsonObject response{
            {"type", "error"},
            {"for", type},
            {"reason", "something is wrong"}
        };
        socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
    }
}

void RequestDispatcher::handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server)
{
    QString name = data["name"].toString();
    QString pw = data["pw"].toString();

    qDebug() << "name은 " << name;
    qDebug() << "pw는 " << pw;

}

