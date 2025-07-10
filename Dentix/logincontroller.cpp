#include "logincontroller.h"
#include "firstscreen.h" //View타입 알아야 Controller에서 캐스팅 가능
#include <QJsonDocument>
#include "mainwindow.h"
LoginController::LoginController(Client *client, QObject *parent)//헤더 생성자 잘 확인하기
    : QObject(parent), m_client(client)
{
    connect(m_client, &Client::loginSuccess, this, &LoginController::onLoginSuccess);
    connect(m_client, &Client::loginFailed, this, &LoginController::onLoginFailed);//loginfailed 확인
}


void LoginController::requestLogin(const QString &name, const QString &pw)
{
    QJsonObject data; //가변적인 data 영역 설정
    data["name"] = name;
    data["pw"] = pw;

    QJsonObject loginInfo;
    loginInfo["type"] = "login";
    loginInfo["data"] = data;

    QJsonDocument doc(loginInfo);
    QByteArray sendedData = doc.toJson();

    m_client->sendJson(sendedData);
}

void LoginController::onLoginSuccess(const QString& userName){
    qDebug() <<"[LoginController] Login success signal received update view";
    emit loginSuccess(userName);
}

void LoginController::onLoginFailed(const QString& reason){
    qDebug() <<"[LoginController] Login success signal received update view";
}



