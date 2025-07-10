#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr); //생성자
    //firstscreen으로 부터 받은 시그널
    void connectToServer(const QString &host, quint16 port);
public slots:
    void sendJson(const QByteArray &jsonData);

signals:
    void loginSuccess(const QString &userName);
    void loginFailed(const QString &reason);

private:
    QTcpSocket* socket; //tcp socket
    QString userName;

private slots:
    void onReadyRead(); //데이터 수신 처리
    void onErrorOccurred(QAbstractSocket::SocketError socketError); //에러 처리
};

#endif // CLIENT_H
