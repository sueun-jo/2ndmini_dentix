#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextLine>
#include <QTextEdit>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "jsonfileio.h"
#include "requestdispatcher.h"

class Server : public QObject
{
    Q_OBJECT
    friend class ProtocolHandler;

public:
    static Server* getInstance(); //싱글턴
    void startServer(quint16 port = 54321); //포트 번호는 54321로 고정한다
    ~Server();

private:
    explicit Server(QObject *parent = nullptr); //생성자는 private
    static Server* instance; //static instance

    QTcpServer *tcpServer;

    RequestDispatcher *requestDispatcher;

    QList<QTcpSocket*> clients; //현재 연결된 모든 클라이언트 소켓 저장용
    QMap<QTcpSocket*, QString> socketToName; // 소켓과 name 매핑

private slots:
    void onNewConnection(); // 새 연결 처리
    void onReadyRead(); // 데이터 수신 처리

};
#endif // SERVER_H
