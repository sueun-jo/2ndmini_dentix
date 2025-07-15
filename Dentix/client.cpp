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
void Client::sendJson(const QByteArray &jsonData)
{

    if(socket->state()== QAbstractSocket::ConnectedState){
        socket->write(jsonData);
        qDebug().noquote()<<"[Client] : Sent to server: "<< jsonData;
    }else{
        qWarning() <<"[Client] : Cannot send data. Socket not connected.";
    }

}

void Client::onReadyRead(){
    QByteArray data = socket->readAll();
    //서버에서 온 데이터 처리 x
    //데이터 처리는 loginController에서
    if(!data.isEmpty()){
        qDebug()<<"[Client]: Raw Data Recevied, passing to controller";
        //로그인 컨트롤러로 데이터 전송
        emit dataReceived(data);
    }
}
void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
}


