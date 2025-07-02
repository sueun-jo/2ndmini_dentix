#include "jsonhandler.h"

JsonHandler::JsonHandler(const QString &filename) {
    filePath = filename;
}

void JsonHandler::appendEntry(const QJsonObject &entry) {
    QFile file(filePath);
    QJsonArray array;

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        array = doc.array(); // 기존 내용 불러오기
        file.close();
    }

    array.append(entry); // 새 항목 추가

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson()); // 덮어쓰기 저장
        file.close();
    }
    else {
        qDebug() << "[JsonHandler] failed to open file for writing " << filePath<< ", error:"
                 << file.errorString();
    }
}
