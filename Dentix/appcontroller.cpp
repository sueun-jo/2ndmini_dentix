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
    m_dataDispatcher = new DataDispatcher(this);
    m_patientManager = new PatientManager(this);
    m_patientDeleteForm = new PatientDeleteForm(nullptr);
    m_patientAddForm = new PatientAddForm(nullptr);
    m_patientSearchForm = new PatientSearchForm(nullptr);
    m_patientModifyForm = new PatientModifyForm(nullptr);
    setupConnectionsLogin();
    setupConnectionsChat();
    setupConnectionsPatient();
}

void AppController::setupConnectionsLogin()
{
    /***********************+++++dispatcher Connect***********************/

    connect(m_client, &Client::jsonReceivedFromServer, m_dataDispatcher, &DataDispatcher::SignalHandler);

    /***********************+++++Server Connect***********************/

    connect(m_firstScreen, &FirstScreen::connectServerRequest, m_client, &Client::connectToServer);


    /***********************+++++Login Connect************************/

    connect(m_firstScreen, &FirstScreen::loginRequest, m_loginManager, &LoginManager::requestLogin);
    connect(m_loginManager, &LoginManager::sendJsonToClient, m_client, &Client::sendJson);
    connect(m_dataDispatcher, &DataDispatcher::loginReceivedJson, m_loginManager, &LoginManager::setUserName);
    connect(m_loginManager, &LoginManager::loginSuccess, this, &AppController::handleLoginScreenTransition);

    /*----------------------------------------------------------------*/
    //connect(m_userManager, &UserManager::userListUpdated, m_chatBasicform, &ChatBasicForm::updateUserList);

    //chatwindow toolbar setting
    m_mainWindow->getChatWindow()->setChatTabs(m_chatBasicform, m_chatGroupform, m_chatInvitedform);
    m_mainWindow->getPatientWindow()->setPatientTap(m_patientSearchForm, m_patientAddForm,  m_patientDeleteForm, m_patientModifyForm);
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

    connect(m_dataDispatcher, &DataDispatcher::dataSendToBasic, m_chatBasicform, &ChatBasicForm::receiveChatData);

    /*-------------------------------------------g---------------------*/
}

void AppController::setupConnectionsPatient()
{
    connect(m_mainWindow, &MainWindow::requestPatientInfo, m_loginManager, &LoginManager::requestPInfo);
    connect(m_loginManager, &LoginManager::pInfoRequestPassToServer, m_client, &Client::sendJson);
    connect(m_dataDispatcher, &DataDispatcher::patientInfo, m_patientManager, &PatientManager::updatePatientInfo);
    connect(m_patientManager,&PatientManager::updateCompleted, m_patientDeleteForm, &PatientDeleteForm::updatePatientTable);

    connect(m_patientDeleteForm, &PatientDeleteForm::deleteRequest, m_patientManager, &PatientManager::deletePatientJson );
    connect(m_patientManager, &PatientManager::deleteRequestToServer, m_client, &Client::sendJson) ;


    /*deleteform*/
        //search
    connect(m_patientDeleteForm, &PatientDeleteForm::requestSearchPatient, m_patientManager, &PatientManager::findPatient);
    connect(m_patientManager, &PatientManager::searchCompleted, m_patientDeleteForm, &PatientDeleteForm::updatePatientTable);
        //delete
    connect(m_patientDeleteForm, &PatientDeleteForm::deleteRequest, m_patientManager, &PatientManager::deletePatientJson );
    connect(m_patientManager, &PatientManager::deleteRequestToServer, m_client, &Client::sendJson) ;


    /*Search Form*/

    connect(m_patientSearchForm, &PatientSearchForm::requestSearchPatient, m_patientManager, &PatientManager::findPatient);
    connect(m_patientManager, &PatientManager::searchCompleted, m_patientSearchForm, &PatientSearchForm::updatePatientList);

    /*Add Form*/
    connect(m_patientAddForm, &PatientAddForm::requestAddPatient, m_patientManager, &PatientManager::addPatientJson);
    connect(m_patientManager, &PatientManager::sendPatientInfoToServer, m_client, &Client::sendJson) ;
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




