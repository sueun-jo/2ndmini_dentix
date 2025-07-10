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
    void loginSuccess(const QString& userName);
public:
    explicit LoginController(Client *client, QObject *parent = nullptr);//생성자에서 Client 받음
    void setView(QMainWindow* view); // 어떤 view 제어할지 설정
public slots:
    void requestLogin(const QString &name, const QString &pw); //view로부터 요청 받는 슬룟

private slots:
    void onLoginSuccess(const QString &userName);//Model(Client)로 부터 성공 신호를 받는 슬롯
    void onLoginFailed(const QString& reason);//Model(Client)로 부터 실패 신호를 받는 슬롯
private:
    Client *m_client;//Model에 대한 포인터

};

#endif // LOGINCONTROLLER_H
