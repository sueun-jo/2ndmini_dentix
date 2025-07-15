#ifndef CHATREPOSITORY_H
#define CHATREPOSITORY_H

#include <QVector>
#include <QString>
#include "chat.h"

class ChatRepository
{
public:
    bool saveAllChats(const QVector<Chat*>& chats, const QString& filepath);
    QVector<Chat*> loadAllChats(const QString& filepath);
};

#endif // CHATREPOSITORY_H
