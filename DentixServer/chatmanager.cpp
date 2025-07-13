#include "chatmanager.h"
#include "chatrepository.h"

ChatManager::ChatManager() {
}

void ChatManager::logMessage(const Chat& chat){
    QMutexLocker locker(&mutex);
    chatLog.append(chat);

    //매번 저장
    ChatRepository::saveAllChats(chatLog, "chatlog.json");
}
