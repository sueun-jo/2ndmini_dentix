#include "logincontroller.h"
#include "firstscreen.h" //View타입 알아야 Controller에서 캐스팅 가능
#include <QJsonDocument>
#include "mainwindow.h"
LoginController::LoginController(Client *client, QObject *parent)//헤더 생성자 잘 확인하기
    : QObject(parent), m_client(client)
{

    //클라이언트가 주는 로그인 데이터 시그널을 받아서 유저 내임 추출 및 세팅
    connect(m_client, &Client::dataReceived, this, &LoginController::setUserName);
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
//서버로 부터 받은 데이터에서 userName 추출 -> client에 전송
void LoginController::setUserName(const QByteArray &data)
{
    qDebug().noquote()<<"[LoginController] User data recived from Server : "<<QString::fromUtf8(data);

    //받은 데이터에서 유저이름만 추출
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if(parseError.error == QJsonParseError::NoError && doc.isObject()){
        QJsonObject receivedObject = doc.object();

        if(receivedObject.value("type").toString()=="ack"&& receivedObject.value("for").toString() == "login"){
            if(receivedObject.value("status").toString() == "success"){
                QJsonObject dataObject = receivedObject.value("data").toObject();
                QString userName = dataObject.value("name").toString();

                if(!userName.isEmpty()){
                    qDebug()<<"[LoginController] Loginsuccessfull for user:"<<userName;
                    //로그인 성공 시그널 방출 -> firstscreen에서 받으면 창 전환 , client에 userName 전송, 이후 chatcontroller에서 사용
                    emit loginSuccess(userName);
                } else{
                    qDebug()<<"[LoginController] Login failed : User name is missing";
                    emit loginFailed();
                }
            }
        }
    }
}

