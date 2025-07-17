
#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

//관리할 모든 클래스의 헤더 파일 포함
#include "client.h"
#include "loginmanager.h"
#include "firstscreen.h"
#include "chatbasicform.h"
#include "chatmanager.h"
#include "mainwindow.h"
#include "chatgroupform.h"
#include "chatinvitedform.h"
#include "datadispatcher.h"
//#include "usermanager.h"


class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject *parent =nullptr);

    void startApplication();
    void handleLoginScreenTransition();
private:
    void setupConnectionsLogin();
    void setupConnectionsChat();
    // void setupConnectionsPatient();

    //관리할 모든 객체들 포인터 변수 선언
    Client *m_client;
    LoginManager *m_loginManager;
    MainWindow *m_mainWindow;
    FirstScreen *m_firstScreen;
    //UserManager *m_userManager;


    ChatManager *m_chatManager;
    ChatBasicForm* m_chatBasicform;
    ChatGroupForm* m_chatGroupform;
    ChatInvitedForm* m_chatInvitedform;

    DataDispatcher* m_dataDispatcher;
};

#endif // APPCONTROLLER_H
