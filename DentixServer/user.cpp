#include "user.h"

User::User() : name(), pw(""), socket(nullptr) {}

User::User(const QString& name, const QString& pw)
    : name(name), pw(pw), socket(nullptr) {}

User::User(const QString& name, const QString& pw, QTcpSocket* socket)
    : name(name), pw(pw), socket(socket) {}

/* getter, setter */
QString User::getName() const { return name;}

QString User::getPassword() const { return pw; }

QTcpSocket* User::getSocket() const { return socket; }

void User::setSocket(QTcpSocket* s) { socket = s; }
void User::setName(const QString& nameInput) { name = nameInput;}

/* user 객체를 toJson */
QJsonObject User::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["pw"] = pw;
    return obj;
}

/* QJsonObject에서 fromJson으로 읽어오기 */
User User::fromJson(const QJsonObject& obj) {
    QString name = obj["name"].toString();
    QString pw = obj["pw"].toString();

    return User(name, pw);
}
