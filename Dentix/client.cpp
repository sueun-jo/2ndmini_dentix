#include "client.h"

Client::Client(QObject *parent){
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
}

void Client::connectToServer(const QString &host, quint16 port){
    socket->connectToHost(host, port);
}

void Client::sendNameAsJson(const QString &name){
    QJsonObject json;
    json["name"] = name; // "name"키에 이름 저장

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(); //json 직렬화

    socket->write(data); //서버로 전송
    socket->flush(); //즉시 전송
    qDebug() << "[Client] Sent JSON:" << data;

}

void Client::onReadyRead(){
    QByteArray data = socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
}
