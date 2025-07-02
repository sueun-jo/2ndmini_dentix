#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>

class JsonHandler
{
public:
    JsonHandler(const QString &filename);
    void appendEntry(const QJsonObject &entry);
private:
    QString filePath;
};

#endif // JSONHANDLER_H
