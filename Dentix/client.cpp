#include "client.h"

Client::Client(QObject *parent){
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead());
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
}

void Client::connectToServer(const QString &host, quint16 port){
    socket->connectToHost(host, port);
}

void Client::onReadyRead(){
    QByteArray data = socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "Socket Error: " << socketError << socket->errorString();
}
