#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QJsonObject>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr); //생성자
    void connectToServer(const QString &host, quint16 port); //서버 연결
    void requestLogin(const QString& name, const QString &pw);
    void sendJson(const QJsonObject& obj);

signals:
    void messageReceived(const QString &message); //서버 응답 수신 시

private:
    QTcpSocket* socket; //tcp socket

private slots:
    void onReadyRead(); //데이터 수신 처리
    void onErrorOccurred(QAbstractSocket::SocketError socketError); //에러 처리
};

#endif // CLIENT_H
