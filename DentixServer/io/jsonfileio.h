#ifndef JSONFILEIO_H
#define JSONFILEIO_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QDir>

class JsonFileIO
{
public:

    static QJsonArray readJsonArray(const QString& filepath); //배열기반 json
    static bool writeJsonFile(const QString& filePath, const QJsonArray& array); //json파일 쓰는 용도


private:

};

#endif // JSONFILEIO_H
