#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

class User
{
public:
    User();
    User(const QString& name, const QString& pw, bool isOnline, int socketNumber);
    QJsonObject toJson() const;
    static User fromJson(const QJsonObject& obj);

    QString getName() const;
    QString getPassword() const;
    bool isOnline() const;
    int getSocketNumber() const;

    void setOnline(bool online);


private:
    QString name;
    QString pw;
    bool online;
    int socketNumber;
};

#endif // USER_H
