
#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

//관리할 모든 클래스의 헤더 파일 포함
#include "client.h"


#include "datadispatcher.h"
#include "mainwindow.h"
#include "loginmanager.h"
#include "firstscreen.h"

#include "chatbasicform.h"
#include "chatmanager.h"
#include "chatwindow.h"
#include "chatgroupform.h"
#include "chatinvitedform.h"


#include "patientwindow.h"
#include "patientmanager.h"
#include "patientdeleteform.h"
#include "patientaddform.h"
#include "patientmodifyform.h"
#include "patientsearchform.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject *parent =nullptr);

    void startApplication();
    void handleLoginScreenTransition();
    void handleChatWindow();
    void handlePatientWindow();
    void showMainWindow();
private:
    void setupConnectionsLogin();
    void setupConnectionsChat();
    void setupConnectionsPatient();

    //관리할 모든 객체들 포인터 변수 선언
    Client *m_client;
    LoginManager *m_loginManager;
    MainWindow *m_mainWindow;
    FirstScreen *m_firstScreen;

    ChatWindow *m_chatWindow;
    ChatManager *m_chatManager;
    ChatBasicForm* m_chatBasicform;
    ChatGroupForm* m_chatGroupform;
    ChatInvitedForm* m_chatInvitedform;

    PatientWindow *m_patientWindow;
    PatientSearchForm* m_patientSearchForm; // 이들이 빠져있음
    PatientAddForm* m_patientAddForm;
    PatientDeleteForm* m_patientDeleteForm;
    PatientModifyForm* m_patientModifyForm;

    PatientManager* m_patientManager;
    DataDispatcher* m_dataDispatcher;
};

#endif // APPCONTROLLER_H
