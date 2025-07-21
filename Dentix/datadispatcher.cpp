#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "datadispatcher.h"

DataDispatcher::DataDispatcher(QObject *parent)
    : QObject(parent) {}

void DataDispatcher::SignalHandler(const QByteArray &data)
{
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseErr);

    if (parseErr.error != QJsonParseError::NoError) {
        qWarning() << "[SignalDispatcher] JSON Parse Error:" << parseErr.errorString();
        return;
    }
    if (!doc.isObject()) {
        qWarning() << "[SignalDispatcher] Invalid JSON structure";
        return;
    }
    QJsonObject obj = doc.object();
    QString type = obj["for"].toString();

    if (type == "login") {
        qDebug()<<"Dispatcher: login"<<QString::fromUtf8(data);
        emit loginReceivedJson(data);  // 로그인 응답 // 시그널 이름 바꾸기
    }
    else if (type == "chat") {
        qDebug()<<"Dispatcher: chat"<<QString::fromUtf8(data);
        chatSignalHandler(data);  // 채팅 메시지
    } else if(type == "requestPatientInfo"){
        qDebug()<<"Dispatcher: PatientInfo"<<QString::fromUtf8(data);
        emit patientInfo(data);
    }
}





void DataDispatcher::chatSignalHandler(const QByteArray &data)
{
    qDebug()<<"chatSignalHandler : "<<QString::fromUtf8(data);
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseErr);

    if (parseErr.error != QJsonParseError::NoError) {
        qWarning() << "[SignalDispatcher] JSON Parse Error:" << parseErr.errorString();
        return;
    }
    if (!doc.isObject()) {
        qWarning() << "[SignalDispatcher] Invalid JSON structure";
        return;
    }

    QJsonObject obj = doc.object();
    QString type = obj["for"].toString();

     if (type == "chat") {
        emit dataSendToBasic(data);
    } //else if (type == "그룹채팅") {
    //     emit dataSendToGroup(data);  // 채팅 메시지
    // } else if (type == "초대된채팅") {
    //     emit dataSendToInvtied(data);  // 채팅 메시지
    // } else { qDebug() << "[SignalDispatcher] Unknown type:" << type; }


}
