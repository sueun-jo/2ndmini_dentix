#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QTcpServer>
#include <QJsonObject>

#include "chatmanager.h"
#include "usermanager.h"
#include "patientmanager.h"

class Server; //포인터 사용하고 싶어용

class RequestDispatcher
{
public:
    static void handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server,
                              UserManager* userManager, PatientManager* patientManager, ChatManager* chatManager);
    static void handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager);
    static void handleChat(QTcpSocket* socket, const QJsonObject& data, Server* server,
                           ChatManager* chatManager, UserManager* userManager);
    static void handlePatientInfoRequest(QTcpSocket* socket, PatientManager* patientManager);
    static void handleUserListRequest(QTcpSocket* socket, UserManager* userManager);
    static void handleAddPatient(QTcpSocket* socket, const QJsonObject& data, PatientManager* patientManager);
    static void handleDeletePatient(QTcpSocket* socket, const QJsonObject& data, PatientManager* patientManager);
    static void handleModifyPatient(QTcpSocket* socket, const QJsonObject& data, PatientManager* patientManager);

    static QJsonArray getOnlineUserNamesArray(UserManager* manager);
};

#endif // REQUESTDISPATCHER_H
