#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include "user.h"
#include "userrepository.h"

class UserManager
{
public:
    UserManager();
    bool login(const QString& name, const QString& pw);
    void setOnlineStatus(const QString& name, bool online);
    QVector<User> getAllUsers() const;

private:
    QVector<User> users;
    UserRepository repository;
};

#endif // USERMANAGER_H
