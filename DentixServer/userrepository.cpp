#include "userrepository.h"
#include "jsonfileio.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

QVector<User> UserRepository::loadAllUsers(const QString& filepath)
{
    QVector<User> users;
    QJsonArray arr = JsonFileIO::readJsonArray(filepath);

    for (const QJsonValue& val : arr) {
        users.append(User::fromJson(val.toObject()));
    }

    qDebug() << "[UserRepository] 등록된 총 사용자 수:" << users.size();
    return users;
}

bool UserRepository::saveAllUsers(const QVector<User>& users, const QString& filepath)
{
    QJsonArray arr;
    for (const User& user : users) {
        arr.append(user.toJson());
    }

    return JsonFileIO::writeJsonFile(filepath, arr);
}
