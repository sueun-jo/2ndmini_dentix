#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>

class Client : public QObject
{
public:
    explicit Client(QObject *parent = nullptr); //기본 생성자
    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message); //이게 socket 통신에서 send 같은 거인듯

signals:
    void messageReceived(const QString &message); //UI에서 연결될 시그널

private:
    QTcpSocket* socket;

private slots:
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
};

#endif // CLIENT_H
