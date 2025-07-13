#include "chat.h"
#include <QDebug>

Chat::Chat (const QString& senderName,
            const QString& chatRoomId,
            const QString& content,
            MessageType type,
            const QDateTime& timestamp)
    // 멤버 변수 초기화
    : m_messageId(QUuid::createUuid().toString()), // 새로운 메시지마다 고유 ID 자동 생성
    m_sender(senderName),
    m_chatRoomId(chatRoomId),
    m_messageContent(content),
    m_messageType(type),
    m_timestamp(timestamp)
{
    //생성자 본문 딱히 쓸 것 없음
}

/* getter 구현부 */
QString Chat::getMessageId() const {
    return m_messageId;
}
QString Chat::getSender() const {
    return m_sender;
}

QString Chat::getChatRoomID() const {
    return m_chatRoomId;
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

    return QString("Time: %1 | ID: %2 | Room: %3 | Sender: %4 | Type: %5 | Content: \"%6\"")
        .arg(m_timestamp.toString("yyyy-MM-dd hh:mm:ss.zzz")) //타임스탬프
        .arg(m_messageId)
        .arg(m_chatRoomId)
        .arg(m_sender)
        .arg(typeStr)
        .arg(m_messageContent);
    }
}
