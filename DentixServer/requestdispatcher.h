#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QTcpServer>
#include <QJsonObject>

#include "usermanager.h"
#include "patientmanager.h"

class Server; //포인터 사용하고 싶어용

class RequestDispatcher
{
public:
    static void handleRequest(QTcpSocket* socket, const QJsonObject& obj, Server* server, UserManager* userManager, PatientManager* patientManager);
    static void handleLogin(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager);
    static void handleChat(QTcpSocket* socket, const QJsonObject& data, Server* server, UserManager* userManager);
    static void handleUpdatePatients(QTcpSocket* socket, const QJsonValue& data, PatientManager* patientManager);
};

#endif // REQUESTDISPATCHER_H
