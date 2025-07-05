#include "client.h"

Client::Client(QObject *parent){
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
}

void Client::connectToServer(const QString &host, quint16 port){
    socket->connectToHost(host, port);

    if (!socket->waitForConnected(1000)){
        qWarning() << "[Client] Cannot connect to Server." << socket->errorString();
    } else {
        qDebug() << "[Client] Connection is established.";
    }
}

void Client::requestLogin(const QString &name, const QString& pw){

    QJsonObject data; //가변적인 data
    data["name"] = name;
    data["pw"] = pw;

    QJsonObject loginInfo;
    loginInfo["type"] = "login";
    loginInfo["data"] = data;

    sendJson(loginInfo);
}

void Client::sendJson(const QJsonObject &obj){

    QJsonDocument doc(obj); //json객체를 doc으로 만듦
    QByteArray sendedData = doc.toJson(); //json을 문자열로 변환해서 QByteArray로 만든다
    qDebug().noquote() << "[Client] send json to server: "<< doc.toJson(QJsonDocument::Compact);

    socket->write(sendedData); // 버퍼에 데이터를 적고
    socket->flush(); //서버에 전송한다
}

void Client::onReadyRead(){ //서버로부터 읽을 게 있을 때
    QByteArray data = socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
}
