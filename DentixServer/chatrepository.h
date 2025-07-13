#ifndef CHATREPOSITORY_H
#define CHATREPOSITORY_H

#include "chat.h"

class ChatRepository
{
public:
    static bool saveAllChats(const QVector<Chat>& chats, const QString& filepath);
    static QVector<Chat> loadAllChats(const QString& filepath);
};

#endif // CHATREPOSITORY_H
