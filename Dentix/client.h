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
signals:
    //서버로 부터 온 데이터 loginController로 보내는 시그널
    void jsonReceivedFromServer(const QByteArray &data);

public:
    explicit Client(QObject *parent = nullptr); //생성자
    //firstscreen으로 부터 받은 연결시그널

public slots:
    void sendJson(const QByteArray &jsonData);
    bool connectToServer(const QString &host, quint16 port);
    void sendRaw(const QByteArray &chunk);
private:
    QTcpSocket* socket; //tcp socket
    //loginController가 주는 userName 저장용 문자열 변수


private slots:
    void onReadyRead(); //데이터 수신 처리
    void onErrorOccurred(QAbstractSocket::SocketError socketError); //에러 처리


};

#endif // CLIENT_H
