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
    void setupConnectionsPatient();

    //관리할 모든 객체들 포인터 변수 선언
    Client *m_client;
    LoginManager *m_loginManager;
    MainWindow *m_mainWindow;
    FirstScreen *m_firstScreen;


    ChatManager *m_chatManager;
    ChatBasicForm* m_chatBasicform;
    ChatGroupForm* m_chatGroupform;
    ChatInvitedForm* m_chatInvitedform;
};

#endif // APPCONTROLLER_H
//setupConnections() 메서드 (권장): 시그널-슬롯 연결 로직을 전용 메서드(예: setupConnections())로
//분리하는 것이 좋습니다. 이렇게 하면 생성자를 깔끔하게 유지하고, 필요할 때 연결 로직만 재호출하거나 테스트하기 용이합니다.
