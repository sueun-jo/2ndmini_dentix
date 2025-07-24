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
        socket->flush();
        qDebug().noquote() << "[Client] : Send to server: " << QString::fromUtf8(jsonData);

    }else{
        qWarning() <<"[Client] : Cannot send data. Socket not connected.";
    }
}

// void Client::sendRaw(const QByteArray &chunk)
// {

//     if(socket->state()== QAbstractSocket::ConnectedState){
//         socket->write(chunk);

//         qDebug().noquote() << "[Client] : Send to server image data: " << chunk;//.toBase64();

//     }else{
//         qWarning() <<"[Client] : Cannot send data. Socket not connected.";
//     }
// }

void Client::onReadyRead(){
    static QByteArray buffer;

    buffer += socket->readAll();

    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(buffer, &parseErr);

    if (parseErr.error == QJsonParseError::NoError) {
        qDebug().noquote() << "[Client]: received complete JSON: " << QString::fromUtf8(buffer);
        emit jsonReceivedFromServer(buffer);
        buffer.clear();  // 사용 후 초기화
    } else {
        qDebug() << "[Client]: partial data, waiting for more... (" << parseErr.errorString() << ")";
        // 다음 readAll()까지 누적
    }
}
void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
}


