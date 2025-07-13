#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QObject>
#include <QMutex>
#include "chat.h"
#include "chatrepository.h"

class ChatManager
{
public:
    void logMessage(const Chat& chat);
    QVector<Chat> getAllChats() const;
    ChatManager();

private:
    QVector<Chat> chatLog; //chatLog로 저장할 QVector
    QMutex mutex;          // mutex
    ChatRepository chatrepository;

};

#endif // CHATMANAGER_H
