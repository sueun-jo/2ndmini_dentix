#include "jsonhandler.h"

JsonHandler::JsonHandler(const QString &filename) {
    filePath = filename;
    qDebug() << "[JsonHandler] 파일 경로 설정됨: " << filePath;
}

void JsonHandler::appendEntry(const QJsonObject &entry) {
    QFile file(filePath);
    QJsonArray array;

    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "[JsonHandler] 파일 열기 성공 " << filePath;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        array = doc.array(); // 기존 내용 불러오기
        file.close();
    }
    else {
        qDebug() << "[JsonHandler] 기존 파일 없음 혹은 읽기 실패:" << filePath;
    }

    array.append(entry); // 새 항목 추가


    if (file.open(QIODevice::WriteOnly)) {
        qDebug() << "[JsonHandler] 파일 열기 성공 (쓰기):" << filePath;
        file.write(QJsonDocument(array).toJson()); // 덮어쓰기 저장
        file.close();
        qDebug() << "[JsonHandler] JSON 저장 완료.";
        qDebug() << "JSON 파일 저장 경로:" << QDir::currentPath();
    }
    else {
        qDebug() << "[JsonHandler] 저장 실패:" << file.errorString();
    }
}
