#include "requestdispatcher.h"
#include "server.h"
#include "usermanager.h"
#include "patientmanager.h"
#include "logutil.h"
#include "responsefactory.h"
#include "jsonfileio.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

void RequestDispatcher::handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server, UserManager* userManager, PatientManager* patientManager) {
    QString type = obj["type"].toString();
    QJsonObject data = obj["data"].toObject();

    if (type == "login") {
        handleLogin(socket, data, server, userManager);
    } else if (type == "updatePatients"){
        handleUpdatePatients(socket, data, patientManager);

    } else {
        QJsonObject response{
            {"type", "error"},
            {"for", type},
            {"reason", "unknown request type"}
        };
        socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
        socket->flush();
    }
}

void RequestDispatcher::handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager) {
    QString nameInput = data["name"].toString();
    QString pwInput = data["pw"].toString();

    dprint("[RequestDispatcher] login 요청 분기");

    QJsonObject response = userManager->login(nameInput, pwInput);

    socket->write(QJsonDocument(response).toJson(QJsonDocument::Indented));
    socket->flush();
}

void RequestDispatcher::handleUpdatePatients(QTcpSocket* socket, const QJsonValue& data, PatientManager* patientManager){
    QJsonArray arr = data["patients"].toArray();
    QVector<Patient> updatedPatients;

    for (const QJsonValue& val : arr) {
        if (!val.isObject()) continue;
        updatedPatients.append(Patient::fromJson(val.toObject()));
    }

    QJsonObject response;

    // patientManager->setAllPatients 하고 return값을 기반으로 분기
    if (patientManager->setAllPatients(updatedPatients)) { //성공
        response = ResponseFactory::createResponse("updatePatients", "success");
    } else { // 실패
        response = ResponseFactory::createResponse("updatePatients", "fail",
                                                   {{"reason", "서버 파일 저장에 실패했습니다."}});
    }

    // 생성된 응답을 클라이언트에 전송
    socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
    socket->flush();
}
