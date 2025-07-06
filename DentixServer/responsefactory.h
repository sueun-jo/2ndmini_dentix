#ifndef RESPONSEFACTORY_H
#define RESPONSEFACTORY_H

#include <QJsonObject>

class ResponseFactory {
public:
    static QJsonObject createResponse(const QString& forType, const QString& status);
    static QJsonObject createResponse(const QString& forType, const QString& status, const QJsonObject& data);
};

#endif // RESPONSEFACTORY_H
