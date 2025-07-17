#include "responsefactory.h"
#include "logutil.h"

/* ResponseFactory는 클라이언트에 보낼 response만 생성한다 */
QJsonObject ResponseFactory::createResponse(const QString& forType, const QString& status) {
    QJsonObject obj;
    obj["type"] = "ack";
    obj["for"] = forType;
    obj["status"] = status;
    return obj;
    qDebug ()<<"[ResponseFactory] 응답 생성: " << QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QJsonObject ResponseFactory::createResponse(const QString& forType, const QString& status, const QJsonObject& data) {
    QJsonObject obj;
    obj["type"] = "ack";
    obj["for"] = forType;
    obj["status"] = status;
    obj["data"] = data;
    dprint("[ResponseFactory] 응답 생성: ") << QJsonDocument(obj).toJson(QJsonDocument::Compact);
    return obj;
}
