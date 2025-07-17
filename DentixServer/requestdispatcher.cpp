#include "requestdispatcher.h"
#include "server.h"
#include "usermanager.h"
#include "patientmanager.h"
#include "chatmanager.h"
#include "responsefactory.h"
#include "jsonfileio.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

void RequestDispatcher::handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server,
                                      UserManager* userManager, PatientManager* patientManager,
                                                                    ChatManager *chatManager) {
    QString type = obj["type"].toString(); //type
    QJsonObject data = obj["data"].toObject(); //data (가변)

    if (type == "login") {
        handleLogin(socket, data, server, userManager);
    } else if (type == "updatePatients"){
        handleUpdatePatients(socket, data, patientManager);
    } else if ( type == "chat"){
        handleChat(socket, data, server, chatManager, userManager);
    }
    else {
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

    qDebug() << "[RequestDispatcher] login 요청 분기";
    User* user = userManager->findUserBySocket(socket);

    QJsonObject response = userManager->login(nameInput, pwInput, socket);

    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

void RequestDispatcher::handleUpdatePatients(QTcpSocket* socket, const QJsonValue& data, PatientManager* patientManager){
    QJsonArray arr = data["patients"].toArray();
    QVector<Patient> updatedPatients;

    for (const QJsonValue& val : arr) {
        if (!val.isObject()) continue;
        updatedPatients.append(Patient::fromJson(val.toObject()));
    }

    QJsonObject response;

    // patientManager->setAllPatients 하고 return값을 기반으로 분기
    if (patientManager->setAllPatients(updatedPatients)) { //성공
        response = ResponseFactory::createResponse("updatePatients", "success");
    } else { // 실패
        response = ResponseFactory::createResponse("updatePatients", "fail",
                                                   {{"reason", "서버 파일 저장에 실패했습니다."}});
    }
    // 생성된 응답을 클라이언트에 전송
    socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
    socket->flush();
}

void RequestDispatcher::handleChat(QTcpSocket* socket,const QJsonObject& data,Server* server,
                                   ChatManager* chatManager, UserManager* userManager){
    Chat *chat = new Chat (Chat::fromJson(data));
    chatManager->addChat(chat);

    if (chat->getChatRoomID() == "전체채팅"){
        const QVector<User*>& onlineUsers = userManager->getOnlineUsers();

        QJsonObject dataObj;
        dataObj["chatRoomID"] = chat->getChatRoomID();
        dataObj["messageContent"] = chat->getMessageContent();
        dataObj["sender"] = chat->getSender();

        QJsonObject response = ResponseFactory::createResponse("chat", "success", dataObj);

        for (User* user : onlineUsers){
            QTcpSocket* sock = user->getSocket();
            if (sock && sock->state() == QAbstractSocket::ConnectedState){
                sock->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
                sock->flush();
            }
        }
    }

    //추후 다른 채팅일때 분기

}
