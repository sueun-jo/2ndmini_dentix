#include "chatrepository.h"
#include "jsonfileio.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

bool ChatRepository::saveAllChats(const QVector<Chat*>& chats, const QString& filepath){
    QJsonArray chatArray;
    for (const Chat* chat : chats){
        if (chat){
            chatArray.append(chat->toJson());
        }
    }

    bool result = JsonFileIO::writeJsonFile(filepath, chatArray);

    if (result) {
        qDebug() << "[ChatRepo] 채팅 로그 저장 성공: " << filepath;
    } else {
        qWarning() << "[ChatRepo] 채팅 로그 저장 실패: " << filepath;
    }
    return result;
}

QVector<Chat*> ChatRepository::loadAllChats(const QString& filepath){
    QVector<Chat*> chats;
    QJsonArray chatArray = JsonFileIO::readJsonArray(filepath);

    for (const QJsonValue& val : chatArray){
        if (val.isObject()){
            Chat* chat = new Chat(Chat::fromJson(val.toObject()));
            chats.append(chat);
        }
    }

    qDebug() << "[ChatRepo] 채팅 로그 로딩 완료";
    return chats;
}



