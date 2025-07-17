#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>
#include <QTcpSocket>

class User
{
public:
    User();
    User(const QString& name, const QString& pw );
    User(const QString& name, const QString& pw, QTcpSocket* socket);
    QJsonObject toJson() const;
    static User fromJson(const QJsonObject& obj);

    /* getter setter*/
    QString getName() const;
    QString getPassword() const;

    QTcpSocket* getSocket() const;

    void setOnline(bool online);
    void setSocket(QTcpSocket* s);

    void setName(const QString& nameInput);


private:
    QString name;
    QString pw;
    QTcpSocket* socket;
};

#endif // USER_H
