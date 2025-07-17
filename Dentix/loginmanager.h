#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMainWindow>
class LoginManager : public QObject
{
    Q_OBJECT
signals:
    void loginSuccess();
    void loginFailed();
    void sendUserName(const QString &userName);
    void sendJsonToClient(const QByteArray &jsonData);
public:
    explicit LoginManager(QObject *parent = nullptr);//생성자에서 Client 받음

public slots:
    void requestLogin(const QString &name, const QString &pw); //view로부터 요청 받는 슬룟

    void setUserName(const QByteArray &data);

};

#endif // LOGINMANAGER_H
