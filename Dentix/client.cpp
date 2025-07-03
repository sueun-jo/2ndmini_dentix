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
    /* json 만들고 보내는 로직*/
    QJsonObject json; //비어있는 Json객체 생성
    json["name"] = name; // "name"키에 이름 저장

    QJsonDocument doc(json); //Json obj를 Json Doc으로 감싼다 : 네트워크로 보내기 좋게 packing
    QByteArray data = doc.toJson(); //json을 문자열로 변환해서 QByteArray로 만든다

    socket->write(data); // 버퍼에 데이터를 적는다
    socket->flush(); //서버에 즉시 전송한다
    qDebug() << "[Client] Sent JSON:" << data;
}

void Client::onReadyRead(){
    QByteArray data = socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
}
