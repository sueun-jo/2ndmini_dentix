#include "requestdispatcher.h"
#include "server.h"
#include "usermanager.h"
#include "logutil.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

void RequestDispatcher::handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server, UserManager* userManager) {
    QString type = obj["type"].toString();
    QJsonObject data = obj["data"].toObject();

    if (type == "login") {
        handleLogin(socket, data, server, userManager);
    } else {
        QJsonObject response{
            {"type", "error"},
            {"for", type},
            {"reason", "unknown request type"}
        };
        socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
        socket->flush();
    }
}

void RequestDispatcher::handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager) {
    QString nameInput = data["name"].toString();
    QString pwInput = data["pw"].toString();

    dprint("[RequestDispatcher] login 요청 분기");
    //qDebug() << "[Login 요청]" << nameInput << pwInput;

    QJsonObject response = userManager->login(nameInput, pwInput);

    socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
    socket->flush();
}
