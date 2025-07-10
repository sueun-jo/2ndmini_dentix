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

    if (!data.isEmpty()){
        qDebug().noquote() << "[Client] Received from server:" << QString::fromUtf8(data);

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error == QJsonParseError::NoError && doc.isObject()){
            QJsonObject receivedObject = doc.object();

            // 로그인 응답 처리
            if (receivedObject.contains("type") && receivedObject["type"].toString() == "ack" &&
                receivedObject.contains("for") && receivedObject["for"].toString() == "login")
            {
                if (receivedObject.contains("status") && receivedObject["status"].toString() == "success") {
                    if (receivedObject.contains("data") && receivedObject["data"].isObject()) {
                        QJsonObject dataObject = receivedObject["data"].toObject();
                        if (dataObject.contains("name") && dataObject["name"].isString()) {
                            QString userName = dataObject["name"].toString();
                            emit loginSuccess(userName); // 로그인 성공 시그널 방출
                            qDebug() << "[Client] Login successful for user:" << userName;
                        }
                    }
                } else if (receivedObject.contains("status") && receivedObject["status"].toString() == "fail") {
                    // 로그인 실패 처리
                    QString message = receivedObject.contains("message") ? receivedObject["message"].toString() : "Unknown error";
                    qDebug() << "Login failed:" << message;
                }
            }
        } else {
            qWarning() << "[Client] Failed to parse JSON or not an object:" << parseError.errorString();
        }
    }
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError){
    qWarning() << "[Client] Socket Error: " << socketError << socket->errorString();
    emit loginFailed("Cannot connected server: "+ socket->errorString());
}





