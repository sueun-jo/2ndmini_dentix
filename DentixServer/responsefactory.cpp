#include "responsefactory.h"
#include "logutil.h"
QJsonObject ResponseFactory::createResponse(const QString& forType, const QString& status) {
    QJsonObject obj;
    obj["type"] = "ack";
    obj["for"] = forType;
    obj["status"] = status;
    return obj;
    dprint("[ResponseFactory] 응답 생성: ") << QJsonDocument(obj).toJson(QJsonDocument::Compact);
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
