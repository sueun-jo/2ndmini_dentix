#include "chatmanager.h"
#include <QDebug>//디버깅용
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
    /* 수은 주석 : 이 부분 서버쪽이랑 json파싱할때 맞추려고 살짝 변경했어요*/
    data["sender"] = m_userName;
    data["chatRoomID"] = chatRoomId;
    data["messageContent"] = message;

    QJsonObject chatMessage;
    chatMessage["type"] = "chat";
    chatMessage["data"] = data;

    QJsonDocument doc(chatMessage);
    QByteArray sendedData = doc.toJson();

    qDebug().noquote()<<"[ChatController] Sending to server: "<< sendedData;
    //헤더에 선언헌 포인터로 클라이언트에 전송
    emit chatJsonReadyToSend(sendedData);
}
