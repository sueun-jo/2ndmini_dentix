#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "user.h"
#include <QVector>
#include <QString>

class UserRepository
{
public:
    QVector<User> loadAllUsers(const QString& filepath);
    bool saveAllUsers(const QVector<User>& users, const QString& filepath);
};

#endif // USERREPOSITORY_H
