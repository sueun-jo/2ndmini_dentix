#include "chatmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
ChatManager::ChatManager(QObject *parent) : QObject(parent){}

void ChatManager::setUserName(const QString &userName)
{
    if(!userName.isEmpty()){
        qDebug()<<"Not set username";
    }
    m_userName = userName;
    qDebug() << "[setUserName] this:" << this << ", m_userName:" << m_userName;


}

void ChatManager::handleChatMessage(const QString &message, const QString &chatRoomId)
{
    //message 비어있는지 확인용
    if(message.isEmpty()){
        qDebug()<<"[ChatManager]Error : No message, Cannot send message";
        return;
    }
    qDebug()<< "[ChatManager] Received message from view:"<<message;
    sendMessageToServer(message, chatRoomId);
}
void ChatManager::sendMessageToServer(const QString &message, const QString &chatRoomId)
{
    QJsonObject data;


    data["sender"] = m_userName;
    data["chatRoomID"] = chatRoomId;
    data["messageContent"] = message;

    QJsonObject chatMessage;
        chatMessage["type"] = "chat";
        chatMessage["data"] = data;

    QJsonDocument doc(chatMessage);
    QByteArray sendData = doc.toJson();

    qDebug().noquote()<<"[ChatController] Sending to server: "<< sendData;

    emit chatJsonReadyToSend(sendData);
}



void ChatManager::requestUserList(){

    QJsonObject data;
    data["sender"] = m_userName;

    QJsonObject chatMessage;
    chatMessage["type"] = "requestUserList";
    chatMessage["data"] = data;
    QJsonDocument doc(chatMessage);
    QByteArray sendData = doc.toJson();
    emit requestUserListToServer(sendData);
}
