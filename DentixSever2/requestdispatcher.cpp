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

/* 로그인 로직 */
void RequestDispatcher::handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server)
{
    QString nameInput = data["name"].toString();
    QString pwInput = data["pw"].toString();

    qDebug() << "name은 " << nameInput;
    qDebug() << "pw는 " << pwInput;

    //여기서 users.json 읽어와서 name이랑 pw가 맞는지 확인해야함
    QJsonArray usersArray = JsonHandler::readJsonArray("users.json");
    qDebug().noquote() << QJsonDocument(usersArray).toJson(QJsonDocument::Compact);
    bool status = false; //기본 status는 false

    for (const QJsonValue& userVal : usersArray) {
        QJsonObject userObj = userVal.toObject();
        QString nameStored = userObj["name"].toString();
        QString pwStored = userObj["pw"].toString();

        if (nameStored == nameInput && pwStored == pwInput){
            status = true;
            break;
        }
    }

    QJsonObject response;
    if (status) {
        response["type"] = "ack";
        response["for"] = "login";
        response["success"] = true;
    } else {
        response["type"] = "ack";
        response["for"] = "login";
        response["success"] = false;
        response["reason"] = "no matched name or pw";
    }

    QJsonDocument responseDoc(response);
    qDebug().noquote() << "[서버 응답]" << responseDoc.toJson(QJsonDocument::Compact);

    socket->write(responseDoc.toJson(QJsonDocument::Compact));
    socket->flush();

}

