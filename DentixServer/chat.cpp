#include "chat.h"
#include <QDebug>
#include <QJsonObject>

Chat::Chat (const QString& senderName,
            const QString& chatRoomID,
            const QString& content,
            MessageType type,
            const QDateTime& timestamp)
    // 멤버 변수 초기화
    : /*m_messageId(QUuid::createUuid().toString()),*/ // 새로운 메시지마다 고유 ID 자동 생성
    m_sender(senderName),
    m_chatRoomID(chatRoomID),
    m_messageContent(content),
    m_messageType(type),
    m_timestamp(timestamp)
{
    //생성자 본문 딱히 쓸 것 없음
}

/* getter 구현부 */

// QString Chat::getMessageID() const {
//     return m_messageType;
// }

QString Chat::getSender() const {
    return m_sender;
}

QString Chat::getChatRoomID() const {
    return m_chatRoomID;
}
QString Chat::getMessageContent() const {
    return m_messageContent;
}
Chat::MessageType Chat::getMessageType() const {
    return m_messageType;
}

QDateTime Chat::getTimeStamp() const {
    return m_timestamp;
}

/* 읽기 쉬운 형태로 Chat 객체 내용 보여주는 함수 : 로그 찍을 때 사용할 거임 */
QString Chat::toString() const {
    QString typeStr; //messageType은 enum값 문자열로 변환
    switch (m_messageType) {
    case Text:
        typeStr = "Text";
        break;
    case Image: typeStr = "Image";
        break;
    default:
        typeStr = "Unknown";
        break;
    }
    return QString("Time: %1 | Room: %2 | Sender: %3 | Type: %4 | Content: \"%5\"")
        .arg(m_timestamp.toString("yyyy-MM-dd hh:mm:ss.zzz")) //타임스탬프
        .arg(m_chatRoomID)
        .arg(m_sender)
        .arg(typeStr)
        .arg(m_messageContent);
}

/* json식으로 만들거나 json 식으로 읽어오는 로직 */
QJsonObject Chat::toJson() const {
    QJsonObject chatjson;
    // chatjson["messageID"] = m_messageID;
    chatjson["sender"] = m_sender;
    chatjson["chatRoomID"] = m_chatRoomID;
    chatjson["messageContent"] = m_messageContent;
    chatjson["messageType"] = m_messageType; // Q_ENUM 덕분에 int로 변환됨
    chatjson["timestamp"] = m_timestamp.toString(Qt::ISODate);
    return chatjson;
}

Chat Chat::fromJson(const QJsonObject& chatjson){
    QString sender = chatjson["sender"].toString();
    QString chatRoomID = chatjson["chatRoomID"].toString();
    QString messageContent = chatjson["messageContent"].toString();
    Chat::MessageType messageType = static_cast<Chat::MessageType>(chatjson["messageType"].toInt());
    QDateTime timestamp = QDateTime::fromString(chatjson["timestamp"].toString(), Qt::ISODate);
    return Chat(sender, chatRoomID, messageContent, messageType, timestamp);
}


