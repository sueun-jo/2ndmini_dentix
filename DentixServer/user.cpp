#include "user.h"

User::User() : name(), pw(""), online(false), socket(nullptr) {}

User::User(const QString& name, const QString& pw, bool isOnline)
    : name(name), pw(pw), online(isOnline), socket(nullptr) {}

User::User(const QString& name, const QString& pw, bool isOnline, QTcpSocket* socket)
    : name(name), pw(pw), online(isOnline), socket(socket) {}

/* getter, setter */
QString User::getName() const { return name;}

QString User::getPassword() const { return pw; }

bool User::isOnline() const { return online; }

QTcpSocket* User::getSocket() const { return socket; }

void User::setOnline(bool onlineStatus) { online = onlineStatus; }

void User::setSocket(QTcpSocket* s) { socket = s; }

/* user 객체를 toJson */
QJsonObject User::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["pw"] = pw;
    obj["online"] = online;
    return obj;
}

/* QJsonObject에서 fromJson으로 읽어오기 */
User User::fromJson(const QJsonObject& obj) {
    QString name = obj["name"].toString();
    QString pw = obj["pw"].toString();
    bool online = obj["online"].toBool();

    return User(name, pw, online);
}
