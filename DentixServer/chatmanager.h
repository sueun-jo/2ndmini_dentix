#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QObject>
#include <QVector>
#include "chat.h"
#include "chatrepository.h"

class ChatManager : public QObject
{
    Q_OBJECT
public:
    explicit ChatManager(QObject* parent = nullptr);

    bool addChat(Chat* chat); //채팅 로그에 체팅 추가
    const QVector<Chat*>& getChats() const;

    //테스트용

signals:
    void chatAdded(Chat* chat); //새로운 채팅 들어오면 보낼 signal

private:
    QVector<Chat*> chats;
    ChatRepository chatrepo;
};

#endif // CHATMANAGER_H
