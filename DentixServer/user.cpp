#include "user.h"

User::User() : name(""), pw(""), online(false), socketNumber(0){}

User::User(const QString& name, const QString& pw, bool isOnline, int socketNumber)
    : name(name), pw(pw), online(isOnline), socketNumber(socketNumber) {}

/* getter, setter */
QString User::getName() const {
    return name;
}

QString User::getPassword() const {
    return pw;
}

bool User::isOnline() const {
    return online;
}

int User::getSocketNumber() const {
    return socketNumber;
}

void User::setOnline(bool onlineStatus) {
    online = onlineStatus;
}

/* user 객체를 toJson */
QJsonObject User::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["pw"] = pw;
    obj["online"] = online;
    obj["socket"] = socketNumber;
    return obj;
}

/* QJsonObject에서 fromJson으로 읽어오기 */
User User::fromJson(const QJsonObject& obj) {
    QString name = obj["name"].toString();
    QString pw = obj["pw"].toString();
    bool online = obj["online"].toBool();
    int socket = obj["socket"].toInt();
    return User(name, pw, online, socket);
}
