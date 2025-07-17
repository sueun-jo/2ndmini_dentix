#include "jsonfileio.h"// 클래스 이름 바꾸어야 한다.
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

JsonFileIo::JsonFileIo(QObject *parent)
    : QObject(parent){}

void JsonFileIo::handleRawJson(const QByteArray &data)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    if (err.error != QJsonParseError::NoError) {
        qWarning() << "[JsonIO] JSON Parse Error:" << err.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "[JsonIO] Invalid JSON structure";
        return;
    }

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "ack") {
        emit loginReceivedJson(data);  // 로그인 응답 // 시그널 이름 바꾸기
    }
    else if (type == "chat") {
        emit chatReceivedJson(data);  // 채팅 메시지
    }
    // else if (type == "userList" || type == "userJoin" || type == "userLeave") {
    //     emit userEventReceivedJson(data);  // 접속자 관련
    // }//유저리스트 나중에 구현
    else {
        qDebug() << "[JsonIO] Unknown type:" << type;
    }
}
