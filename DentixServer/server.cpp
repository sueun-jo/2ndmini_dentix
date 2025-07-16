#include "server.h"
#include "logutil.h"

Server* Server::instance = nullptr; //싱글턴 instance 초기화

Server* Server::getInstance(){
    if (!instance)
        instance = new Server();
    return instance;
}

//생성자 (private)
Server::Server(QObject *parent) : QObject (parent)
{
    tcpServer = new QTcpServer(this); //TCP 서버 객체 생성
    //newConnetion 들어오면 onNewConnection 수행 : 슬롯 연결
    connect (tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);
    userManager = new UserManager();
    patientManager = new PatientManager();
    chatManager = new ChatManager();
}

//서버 시작 : 지정 포트로 수신 대기
void Server::startServer(quint16 port){

    if (tcpServer->isListening()){ //이미 열려있으면 알려주는 용도
        qDebug() << "Server is already running on port" << tcpServer->serverPort();
        return;
    }
    if (tcpServer->listen(QHostAddress::Any, port)){
        qDebug() << "Server started on port " << port; // 수신대기
    } else{
        qDebug() << "Server failed " << tcpServer->errorString(); //연결 실패
    }
}

// 새 클라이언트 연결 수락
void Server::onNewConnection(){
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clients.append(clientSocket); //연결된 클라이언트 목록에 추가

    //해당 소켓에서 데이터 수신되면 onReadyRead 호출
    connect (clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);

    // 클라이언트가 연결을 끊었을 때 처리 : 람다
    connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
        clients.removeAll(clientSocket); // 목록에서 제거
        clientSocket->deleteLater();     // 메모리 정리
        qDebug() << "[Server] Client disconnected.";
    });
}

//클라이언트로부터 데이터 수신 됐을 때
void Server::onReadyRead(){
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender()); //어떤 소켓인지 식별
    QByteArray data = socket->readAll(); //수신한 데이터 읽어오기

    QJsonDocument doc = QJsonDocument::fromJson(data); //json형태로 온 데이터 파싱
    if (doc.isObject()){ //읽어서 request 종류 파악하고 handleRequest 따라감
        QJsonObject obj = doc.object();

        //qDebug().noquote() << QJsonDocument(obj).toJson(QJsonDocument::Compact);

        RequestDispatcher::handleRequest(socket, obj, this, userManager, patientManager); //클라이언트 메시지 분기
    }
}

Server::~Server() {
    tcpServer->close(); // 수신 종료

    /* 클라이언트 소켓 정리 */
    for (auto client : clients){
        client->disconnectFromHost();
        client->deleteLater();
    }
    clients.clear(); //목록 비우기
    delete userManager;
    delete patientManager;
}
