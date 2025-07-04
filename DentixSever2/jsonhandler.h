#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QDir>

class JsonHandler
{
public:

    static QJsonArray readJsonArray(const QString& filepath); //배열기반 json
    static bool writeJsonFile(const QString& filePat, const QJsonArray& array); //json파일 쓰는 용도


private:

};

#endif // JSONHANDLER_H
