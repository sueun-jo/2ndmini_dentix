#include "chatcontroller.h"
#include "chatbasicform.h"
#include <QDebug>//디버깅용
#include <QJsonObject>
#include <QJsonDocument>
ChatController::ChatController(Client* client, QObject *parent) : QObject(parent), m_client(client)
{
}

void ChatController::setUserName(const QString userName)
{
    m_userName = userName;
    qDebug()<<"[ChatController] : user set to :" << m_userName;

}



void ChatController::requestMessage(const QString message)
{
    //message 비어있는지 확인용
    if(message.isEmpty()){
        qDebug()<<"[ChatController]Error : No message, Cannot send message";
        return;
    }
    qDebug()<< "[ChatController] Received message from view:"<<message;
    sendMessageToServer(message);

}

void ChatController::sendMessageToServer(QString message)
{
    QJsonObject data;
    data["name"] = m_userName;
    qDebug()<<"userName: "<< m_userName;
    data["message"] = message;

    QJsonObject chatMessage;
    chatMessage["type"] = "chat";
    chatMessage["data"] = data;

    QJsonDocument doc(chatMessage);
    QByteArray sendedData = doc.toJson();

    qDebug()<<"[ChatController] Sending to server: "<< sendedData;
    //헤더에 선언헌 포인터로 클라이언트에 전송
    m_client->sendJson(sendedData);
}
