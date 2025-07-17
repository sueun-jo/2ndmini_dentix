#include "appcontroller.h"
#include <QDebug>


AppController::AppController(QObject *parent) : QObject(parent)
{
    //모든 핵심 객체들 SignalManager의 생성자에서 단 한번만 생성하고 소유
    m_client = new Client(this);
    m_loginManager = new LoginManager(this);
    m_firstScreen = new FirstScreen(nullptr);
    m_chatManager = new ChatManager(this);
    m_mainWindow = new MainWindow(nullptr);

    m_chatBasicform = new ChatBasicForm(nullptr);
    m_chatGroupform = new ChatGroupForm(nullptr);
    m_chatInvitedform = new ChatInvitedForm(nullptr);

    setupConnectionsLogin();
    setupConnectionsChat();
    setupConnectionsPatient();
}

void AppController::setupConnectionsLogin()
{


    /***********************+++++Server Connect***********************/

    connect(m_firstScreen, &FirstScreen::connectServerRequest, m_client, &Client::connectToServer);

    /***********************+++++Login Connect************************/

    connect(m_firstScreen, &FirstScreen::loginRequest, m_loginManager, &LoginManager::requestLogin);
    connect(m_loginManager, &LoginManager::sendJsonToClient, m_client, &Client::sendJson);
    connect(m_client, &Client::jsonReceivedFromServer, m_loginManager, &LoginManager::setUserName);
    connect(m_loginManager, &LoginManager::loginSuccess, this, &AppController::handleLoginScreenTransition);

    /*----------------------------------------------------------------*/


    //chatwindow toolbar setting
    m_mainWindow->getChatWindow()->setChatTabs(m_chatBasicform, m_chatGroupform, m_chatInvitedform);

}

void AppController::setupConnectionsChat()
{

    /***********************+++++Chat Connect**************************/

        /********************Send Message*********************/

    connect(m_loginManager, &LoginManager::sendUserName, m_chatManager, &ChatManager::setUserName);
    connect(m_chatManager, &ChatManager::chatJsonReadyToSend, m_client, &Client::sendJson);

    //chat basic [전체채팅] 메세지 전송
    connect(m_chatBasicform, &ChatBasicForm::sendMessageSubmit, m_chatManager,&ChatManager::handleChatMessage);
    //chat group [그룹채팅] 메세지 전송
    connect(m_chatGroupform, &ChatGroupForm::sendMessageSubmit, m_chatManager,&ChatManager::handleChatMessage);
    //chat invited [초대된 채팅] 메세지 전송
    connect(m_chatInvitedform, &ChatInvitedForm::sendMessageSubmit, m_chatManager,&ChatManager::handleChatMessage);

    /*----------------------------------------------------------------*/

    /********************Receive Message******************/


    /*----------------------------------------------------------------*/
}
void setupConnectionsPatient()
{

}
/********************  View  ******************/

void AppController::startApplication()
{
    m_firstScreen->show();
}

void AppController::handleLoginScreenTransition()
{
    qDebug() << "SignalManager: login success, screen transition .";

    m_firstScreen->hide();
    m_mainWindow->show();

}
/***********************************************/
