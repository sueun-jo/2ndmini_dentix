#include "jsonhandler.h"
#include "jsonhandler.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

QJsonArray JsonHandler::readJsonArray(const QString& filepath) {

    QFile file(filepath);
    qDebug() << "[DEBUG] 현재 실행 경로:" << QDir::currentPath();

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "[JsonHandler] 파일 열기 실패:" << file.errorString();
        return {};
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "[JsonHandler] 파싱 오류:" << parseError.errorString();
        return {};
    }

    if (!doc.isArray()) {
        qWarning() << "[JsonHandler] 배열 형식 JSON 아님.";
        return {};
    }

    return doc.array();
}

bool JsonHandler::writeJsonFile(const QString& filepath, const QJsonArray& array) {
    QFile file(filepath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "[JsonHandler] 파일 열기 실패 (쓰기):" << file.errorString();
        return false;
    }

    QJsonDocument doc(array);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "[JsonHandler] JSON 파일 저장 완료:" << filepath;
    return true;
}
