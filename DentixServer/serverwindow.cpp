#include "serverwindow.h"
#include "ui_serverwindow.h"

#include "serverinfoform.h"
#include "patientinfoform.h"
#include "chatlogform.h"
#include "server.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{

    ui->setupUi(this);

    Server* server = Server::getInstance();
    PatientManager* patientManager = server->getPatientManager();

    ServerInfoForm* serverInfo = new ServerInfoForm(this);
    this->move(50, 50); //thanks to 준혁
    PatientInfoForm* patientInfo = new PatientInfoForm(patientManager, this);
    ChatLogForm* chatLogForm = new ChatLogForm(this);

    connect(chatLogForm, &ChatLogForm::requestSaveChats,
            serverInfo, &ServerInfoForm::requestSaveChats);

    ui->tabWidget->addTab(serverInfo,tr("서버 정보")); //서버 정보 qdebug() 내용 띄울거임
    ui->tabWidget->addTab(patientInfo, tr("환자정보")); // 환자 정보 검색
    ui->tabWidget->addTab(chatLogForm, tr("채팅 로그")); // 채팅 로그
}

ServerWindow::~ServerWindow()
{

    delete ui;
}

void ServerWindow::on_actionPatientTab_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}


void ServerWindow::on_actionChatLog_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
}

void ServerWindow::on_actionstartServer_triggered()
{
    Server::getInstance()->startServer(54321);
}

void ServerWindow::on_actionstopServer_triggered()
{
    ServerInfoForm::instance()->shutdownServer();
}

