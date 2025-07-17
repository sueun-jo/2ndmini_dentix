#ifndef JSONFILEIO_H
#define JSONFILEIO_H

#include <QObject>
#include <QByteArray>

class JsonFileIo : public QObject
{
    Q_OBJECT
public:
    explicit JsonFileIo(QObject *parent = nullptr);

public slots:
    void handleRawJson(const QByteArray &data);

signals:
    void loginReceivedJson(const QByteArray &data);        // LoginManager로 emit
    void chatReceivedJson(const QByteArray &data);       // ChatManager로 emit
    void userEventReceivedJson(const QByteArray &data);  // UserManager로 emit
};

#endif // JSONFILEIO_H
