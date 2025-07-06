#include "requestdispatcher.h"
#include "server.h"
#include "usermanager.h"
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

    qDebug() << "[Login 요청]" << nameInput << pwInput;

    bool status = userManager->login(nameInput, pwInput);

    QJsonObject response;
    response["type"] = "ack";
    response["for"] = "login";
    response["success"] = status;

    if (!status)
        response["reason"] = "no matched name or pw";

    QJsonDocument responseDoc(response);
    qDebug().noquote() << "[서버 응답]" << responseDoc.toJson(QJsonDocument::Compact);

    socket->write(responseDoc.toJson(QJsonDocument::Compact));
    socket->flush();
}
