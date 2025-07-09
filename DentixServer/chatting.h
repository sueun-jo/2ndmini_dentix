#ifndef CHATTING_H
#define CHATTING_H

#include <QObject>
#include <Qstring>
#include <QDateTime>
#include <QUuid> //메시지 고유id 생성하기 위한 헤더 파일

class Chatting : public QObject
{
    Q_OBJECT
public:

    enum MessageType {
        Text,   //보통 채팅 메시지
        Image   // 이미지 파일 (ftp or 경로)
    };
    Q_ENUM(MessageType) //enum쓰려면 필요함


    explicit Chatting(const QString &sender,
                      const QString& chatRoomID,
                      const QString& content,
                      MessageType type = Text,
                      const QDateTime& timestamp = QDateTime::currentDateTime());

    /* getter */
    QString getMessageId() const;
    QString getSender() const;
    QString getChatRoomID() const;
    QString getMessageContent() const;
    MessageType getMessageType() const;
    QDateTime getTimeStamp();

    // for debugging
    QString toString() const;

private:
    QString m_messageId;               //메시지 고유 식별자 (QUid 사용)
    QString m_sender;                  //메세지를 보낸 사용자 name
    QString m_chatRoomId;              // 매시지가 전송된 채팅방의 고유 ID
    QString m_messageContent;          // 메시지 실제 내용
    MessageType m_messageType;         // 메시지 종류 (text인지 image인지)
    QDateTime m_timestamp;             // 메시지 생성 시간
};

#endif // CHATTING_H
