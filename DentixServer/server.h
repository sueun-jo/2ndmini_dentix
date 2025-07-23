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

#include "requestdispatcher.h"
#include "usermanager.h"
#include "patientmanager.h"
#include "chatmanager.h"

class Server : public QObject
{
    Q_OBJECT

public:
    static Server* getInstance(); //싱글턴
    void startServer(quint16 port = 54321); //포트 번호는 54321로 고정한다
    void stopServer();
    ~Server();

private:
    explicit Server(QObject *parent = nullptr); //생성자는 private
    static Server* instance; //static instance

    QTcpServer *tcpServer;

    RequestDispatcher *requestDispatcher;
    UserManager *userManager;
    PatientManager *patientManager;
    ChatManager *chatManager;

public :
    /* 복사 생성자, 대입 연산자 막음 for 싱글턴 */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    PatientManager* getPatientManager() const { return patientManager; }
    ChatManager* getChatManager() const { return chatManager; }
    UserManager* getUserManager() const {return userManager; }

private slots:
    void onNewConnection(); // 새 연결 처리
    void onReadyRead(); // 데이터 수신 처리
};
#endif // SERVER_H
