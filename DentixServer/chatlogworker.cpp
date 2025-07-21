#include "chatlogworker.h"
#include "chatrepository.h"

void ChatLogWorker::saveChats(const QVector<Chat*>& chats, const QString& filepath){
    ChatRepository::saveAllChats(chats, filepath); //파일 저장
    emit saveDone();
}
