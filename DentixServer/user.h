#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>
#include <QTcpSocket>

class User
{
public:
    User();
    User(const QString& name, const QString& pw, bool isOnline);
    User(const QString& name, const QString& pw, bool isOnline, QTcpSocket* socket);
    QJsonObject toJson() const;
    static User fromJson(const QJsonObject& obj);

    /* getter setter*/
    QString getName() const;
    QString getPassword() const;
    bool isOnline() const;
    QTcpSocket* getSocket() const;

    void setOnline(bool online);
    void setSocket(QTcpSocket* s);


private:
    QString name;
    QString pw;
    bool online;
    QTcpSocket* socket;
};

#endif // USER_H
