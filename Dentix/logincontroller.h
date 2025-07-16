#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMainWindow>
#include "client.h" // logincontroller는 client를 알아야 함
class LoginController : public QObject
{
    Q_OBJECT
signals:
    void loginSuccess();
    void loginFailed();
    void sendUserName(const QString &userName);
public:
    explicit LoginController(Client *client, QObject *parent = nullptr);//생성자에서 Client 받음

public slots:
    void requestLogin(const QString &name, const QString &pw); //view로부터 요청 받는 슬룟

private slots:
    void setUserName(const QByteArray &data);
private:
    Client *m_client;//Model에 대한 포인터

};

#endif // LOGINCONTROLLER_H
