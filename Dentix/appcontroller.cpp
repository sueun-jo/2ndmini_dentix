#include "appcontroller.h"
#include <QDebug>


AppController::AppController(QObject *parent) : QObject(parent)
{
     qDebug() << "@@@@@ AppController INSTANCE CREATED @@@@@";
    //모든 핵심 객체들 SignalManager의 생성자에서 단 한번만 생성하고 소유
    m_client = new Client(this);
    m_dataDispatcher = new DataDispatcher(this);


    m_firstScreen = new FirstScreen(nullptr);
    m_loginManager = new LoginManager(this);

    //MainWindow
    m_mainWindow = new MainWindow(nullptr);
    //Chat
    m_chatWindow = new ChatWindow(nullptr);
    m_chatManager = new ChatManager(this);
    m_chatBasicform = new ChatBasicForm(nullptr);
    m_chatGroupform = new ChatGroupForm(nullptr);
    m_chatInvitedform = new ChatInvitedForm(nullptr);
    //Patient
    m_patientWindow = new PatientWindow(nullptr);
    m_patientManager = new PatientManager(this);
    m_patientDeleteForm = new PatientDeleteForm(nullptr);
    m_patientAddForm = new PatientAddForm(nullptr);
    m_patientSearchForm = new PatientSearchForm(nullptr);
    m_patientModifyForm = new PatientModifyForm(nullptr);
    //m_patientWindow = new PatientWindow(m_patientAddForm, m_patientDeleteForm, m_patientSearchForm, m_patientModifyForm, nullptr);

    setupConnectionsLogin();
    setupConnectionsChat();
    setupConnectionsPatient();
    m_patientWindow->setPatientTap(m_patientSearchForm, m_patientAddForm, m_patientDeleteForm, m_patientModifyForm);
    m_chatWindow->setChatTabs(m_chatBasicform);


    connect(m_mainWindow, &MainWindow::requestPatientInfo, this, &AppController::handlePatientWindow);
    connect(m_mainWindow, &MainWindow::requestUserList, this, &AppController::handleChatWindow);
    connect(m_patientWindow, &PatientWindow::backToMainWindow, this, &AppController::showMainWindow);
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

}

void AppController::setupConnectionsChat()
{

    /***********************+++++Chat Connect**************************/
    connect(m_dataDispatcher, &DataDispatcher::updateOnlineUserlist, m_chatBasicform, &ChatBasicForm::userListUpdate);
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
    //환자정보 요청 및 업데이트
    connect(m_mainWindow, &MainWindow::requestPatientInfo, m_loginManager, &LoginManager::requestPInfo);
    connect(m_loginManager, &LoginManager::pInfoRequestPassToServer, m_client, &Client::sendJson);
    connect(m_dataDispatcher, &DataDispatcher::patientInfo, m_patientManager, &PatientManager::updatePatientInfo);
    connect(m_patientManager, &PatientManager::updateCompleted, m_patientDeleteForm, &PatientDeleteForm::updatePatientTable);
    connect(m_patientManager, &PatientManager::updateCompleted, m_patientModifyForm, &PatientModifyForm::updatePatientList);
    connect(m_patientManager, &PatientManager::updateCompleted, m_patientSearchForm, &PatientSearchForm::updatePatientList);
    //접속자 정보 요청 및 업데이트
    connect(m_chatManager, &ChatManager::requestUserListToServer, m_client, &Client::sendJson);
    connect(m_mainWindow, &MainWindow::requestUserList,  m_chatManager, &ChatManager::requestUserList);

    /*deleteform*/
        //search
    connect(m_patientDeleteForm, &PatientDeleteForm::requestSearchPatient, m_patientManager, &PatientManager::findPatient);
    connect(m_patientManager, &PatientManager::searchCompleted, m_patientDeleteForm, &PatientDeleteForm::updatePatientTable);
        //delete
    connect(m_patientDeleteForm, &PatientDeleteForm::deleteRequest, m_patientManager, &PatientManager::deletePatientData );
    connect(m_patientManager, &PatientManager::deleteRequestToServer, m_client, &Client::sendJson) ;


    /*Search Form*/

    connect(m_patientSearchForm, &PatientSearchForm::requestSearchPatient, m_patientManager, &PatientManager::findPatient);
    connect(m_patientManager, &PatientManager::searchCompleted, m_patientSearchForm, &PatientSearchForm::updatePatientList);
    qDebug() << "!!!!!! Connecting PatientSearchForm requestImageToServer to Client::sendJson !!!!!!";
    connect(m_patientSearchForm, &PatientSearchForm::requestImageToServer, m_client, &Client::sendJson);
    /*Add Form*/
    connect(m_patientAddForm, &PatientAddForm::requestAddPatient, m_patientManager, &PatientManager::addPatientData);
    connect(m_patientManager, &PatientManager::sendPatientInfoToServer, m_client, &Client::sendJson) ;
    connect(m_patientManager, &PatientManager::sendImageData, m_client, &Client::sendRaw);
    /*Modify Form*/
        //Search
    connect(m_patientModifyForm, &PatientModifyForm::requestSearchPatient, m_patientManager, &PatientManager::findPatient);
    connect(m_patientManager, &PatientManager::searchCompleted, m_patientModifyForm, &PatientModifyForm::updatePatientInfo);
        //Modify
    connect(m_patientModifyForm, &PatientModifyForm::requestModifyUpdate, m_patientManager, &PatientManager::modifyPatientData);
    connect(m_patientManager, &PatientManager::searchCompleted, m_patientModifyForm, &PatientModifyForm::updatePatientList);
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
void AppController::handlePatientWindow() {
    m_patientWindow->show();
    // 초기 데이터 요청 or 설정도 여기서 수행
}

void AppController::handleChatWindow() {
    m_chatWindow->show();
}

void AppController::showMainWindow() {
    m_patientWindow->hide();
    m_mainWindow->show();
}

/***********************************************/

