#include "responsefactory.h"

/* ResponseFactory는 클라이언트에 보낼 response만 생성한다 */
QJsonObject ResponseFactory::createResponse(const QString& forType, const QString& status) {
    QJsonObject res;
    res["type"] = "ack";
    res["for"] = forType;
    res["status"] = status;

    QJsonDocument doc(res);
    qDebug().noquote()<<"[ResponseFactory] 응답 생성: " << QString::fromUtf8(doc.toJson(QJsonDocument::Indented));
    return res;
}

QJsonObject ResponseFactory::createResponse(const QString& forType, const QString& status, const QJsonObject& data) {
    QJsonObject res;
    res["type"] = "ack";
    res["for"] = forType;
    res["status"] = status;
    res["data"] = data;

    QJsonDocument doc(res);
    qDebug().noquote()<< "[ResponseFactory] 응답 생성 " << QString::fromUtf8(doc.toJson(QJsonDocument::Indented));
    return res;
}
