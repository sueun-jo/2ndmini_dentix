#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include "user.h"
#include "userrepository.h"

class UserManager
{
public:
    UserManager();
    QJsonObject login(const QString& name, const QString& pw, QTcpSocket* socket);
    void setOnlineStatus(const QString& name, bool online);
    QVector<User> getAllUsers() const;
    void connectUser(User* user);
    void disconnectUser(QTcpSocket* socket);
    //User* findUserByName(const QString &name) const;
    User* findUserBySocket(const QTcpSocket* socket) const;
    QVector<User*> getOnlineUsers() const;

private:
    QVector<User*> onlineUsers;
    QVector<User> users;
    UserRepository repository;
};

#endif // USERMANAGER_H
