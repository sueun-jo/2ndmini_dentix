#include "client.h"
Client::Client(QObject *parent){
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);

}

bool Client::connectToServer(const QString &host, quint16 port){
    socket->connectToHost(host, port);

    if (!socket->waitForConnected(1000)){
        qWarning() << "[Client] Cannot connect to Server." << socket->errorString();
        return false;
    } else {
        qDebug() << "[Client] Connection is established.";
        return true;
    }
}
void Client::sendJson(const QByteArray &jsonData)
{

    if(socket->state()== QAbstractSocket::ConnectedState){
        socket->write(jsonData);
<<<<<<< HEAD
        // qDebug()<<"[Client] : Sent to server: "<< jsonData;
        qDebug().noquote() << "[Client] : Sent to server: " << QString::fromUtf8(jsonData);
=======

        qDebug().noquote()<<"[Client] : Send from server: "<< QString::fromUtf8(jsonData);

>>>>>>> 888ff3713d78f20092b397f1ea16f90141ce8ab9
    }else{
        qWarning() <<"[Client] : Cannot send data. Socket not connected.";
    }
}

void Client::onReadyRead(){
    QByteArray data = socket->readAll();
    //서버에서 온 데이터 처리 x
    //데이터 처리는 loginController에서
    if(!data.isEmpty()){

        qDebug()<<"[Client]: recived Data from server, sned to DataDitpatcher "<< QString::fromUtf8(data);

        //로그인 컨트롤러로 데이터 전송
        emit jsonReceivedFromServer(data);
    }
}
void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
}


