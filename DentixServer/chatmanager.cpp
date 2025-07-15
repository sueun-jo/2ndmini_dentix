#include "chatmanager.h"
#include "logutil.h"

ChatManager::ChatManager(QObject* parent) : QObject(parent)
{
    chats = chatrepo.loadAllChats("chats.json");
    dprint("[ChatManager] 채팅 로드 완료: ") << chats.size();
}

bool ChatManager::addChat(Chat* chat){
    if (chat){
        chats.append(chat);
        emit chatAdded(chat); //시그널 발생
        qDebug() << "emit chatAdded signal";
        return true;
    }
    return false;
}

const QVector<Chat*>& ChatManager::getChats() const
{
    return chats;
}
