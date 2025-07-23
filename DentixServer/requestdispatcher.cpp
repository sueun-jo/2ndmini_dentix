#include "requestdispatcher.h"
#include "server.h"
#include "usermanager.h"
#include "patientmanager.h"
#include "chatmanager.h"
#include "responsefactory.h"
#include "jsonfileio.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

void RequestDispatcher::handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server,
                                      UserManager* userManager, PatientManager* patientManager,
                                                                    ChatManager *chatManager) {
    QString type = obj["type"].toString(); //type
    QJsonObject data = obj["data"].toObject(); //data (가변)

    if (type == "login") {
        handleLogin(socket, data, server, userManager);
    } else if ( type == "chat"){
        handleChat(socket, data, server, chatManager, userManager);
    } else if ( type == "requestPatientInfo"){
        handlePatientInfoRequest(socket, patientManager);
    } else if (type == "requestUserList"){
        handleUserListRequest(socket, userManager);
    } else if (type == "add"){
        handleAddPatient(socket, data, patientManager);
    } else if (type == "delete"){
        handleDeletePatient (socket, data, patientManager);
    } else if (type == "modify"){
        handleModifyPatient (socket, data, patientManager);
    } else if (type == "requestPatientImage"){
        //사진 fpt로 전송
    }
    else {
        QJsonObject response{
            {"type", "error"},
            {"for", type},
            {"reason", "unknown request type"}
        };
        socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
        socket->flush();
    }
}

/* login 요청 들어왔을 때 */
void RequestDispatcher::handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager) {
    QString nameInput = data["name"].toString();
    QString pwInput = data["pw"].toString();

    qDebug() << "[RequestDispatcher] login 요청 분기";
    User* user = userManager->findUserBySocket(socket);

    QJsonObject response = userManager->login(nameInput, pwInput, socket);

    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

/* chat 들어왔을 때 */
void RequestDispatcher::handleChat(QTcpSocket* socket,const QJsonObject& data,Server* server,
                                   ChatManager* chatManager, UserManager* userManager){
    Chat *chat = new Chat (Chat::fromJson(data));
    chatManager->addChat(chat);

    if (chat->getChatRoomID() == "전체채팅"){
        const QVector<User*>& onlineUsers = userManager->getOnlineUsers();

        QJsonObject dataObj;
        dataObj["chatRoomID"] = chat->getChatRoomID();
        dataObj["messageContent"] = chat->getMessageContent();
        dataObj["sender"] = chat->getSender();
        dataObj["onlineUserNames"] = getOnlineUserNamesArray(userManager);

        QJsonObject response = ResponseFactory::createResponse("chat", "success", dataObj);

        for (User* onlineUser : onlineUsers){ //onlineUser를 하나씩 순회
            QTcpSocket* sock = onlineUser->getSocket(); //sock에다가 onlineUser의 socket값 가져옴
            if (sock && sock->state() == QAbstractSocket::ConnectedState){
                sock->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
                sock->flush();
            }
        }
    }
    //추후 다른 채팅일때 분기 (ex. 김호원의 방, 조수은의 방 등) +@
}


void RequestDispatcher::handlePatientInfoRequest(QTcpSocket* socket, PatientManager* patientManager){
    QVector<Patient> allPatients = patientManager->getAllPatients();

    QJsonArray patientarr;
    for (const Patient& p : allPatients){
        patientarr.append(p.toJson());
    }

    QJsonObject patientObj;
    patientObj["patients"] = patientarr;

    QJsonObject response = ResponseFactory::createResponse("requestPatientInfo", "success", patientObj);
    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

/* userlist 요청 들어오면 */
void RequestDispatcher::handleUserListRequest(QTcpSocket* socket, UserManager* manager){

    QJsonObject nameObj;
    nameObj["onlineUserNames"] = getOnlineUserNamesArray(manager);

    QJsonObject response = ResponseFactory::createResponse("requestUserList", "success", nameObj);
    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

void RequestDispatcher::handleAddPatient(QTcpSocket* socket, const QJsonObject& data, PatientManager* patientManger){
    Patient newPatient = Patient::fromJson(data); //클라이언트한테서 받은 data파싱
    bool ret = patientManger->addPatient(newPatient);

    QJsonObject response;
    if (ret) {
        response = ResponseFactory::createResponse("add", "success");
    } else {
        response = ResponseFactory::createResponse("add", "fail", {{"reason", "failed to add patient."}});
    }

    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

void RequestDispatcher::handleDeletePatient(QTcpSocket* socket, const QJsonObject& data, PatientManager* patientManager){
    qDebug() << "[handleDeletePatient] data:" << data;
    QString name = data["name"].toString().trimmed();
    qDebug() << "삭제 요청 이름:" << name;
    bool ret = patientManager->deletePatient(name);

    qDebug()<< "ret값 in R.D handleDeletePatient : " << ret;
    QJsonObject response;
    if (ret){
        response = ResponseFactory::createResponse("delete", "success");
    } else {
        response = ResponseFactory::createResponse("delete", "fail", {{"reason", "failed to delete patient."}});
    }
    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

/* 환자 정보 수정 */
void RequestDispatcher::handleModifyPatient(QTcpSocket* socket, const QJsonObject& data, PatientManager* patientManger){

    bool ret = patientManger->modifyPatient(data);

    QJsonObject response;
    if (ret){
        response = ResponseFactory::createResponse("delete", "success");
    } else {
        response = ResponseFactory::createResponse("delete", "fail", {{"reason", "failed to modify patient."}});
    }
    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

//이름 보내줄 func
QJsonArray RequestDispatcher::getOnlineUserNamesArray(UserManager* manager) {
    QJsonArray arr;
    const QVector<User*>& onlineUsers = manager->getOnlineUsers();
    for (User* user : onlineUsers) {
        arr.append(user->getName());
    }
    return arr;
}
