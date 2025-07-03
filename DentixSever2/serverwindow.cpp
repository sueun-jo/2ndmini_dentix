#include "serverwindow.h"
#include "ui_serverwindow.h"

#include "serverinfoform.h"
#include "patientinfoform.h"
#include "chatlog.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    ServerInfoForm* serverInfo = new ServerInfoForm(this);
    PatientInfoForm* patientInfo = new PatientInfoForm(this);
    ChatLog* chatLog = new ChatLog(this);
    ui->tabWidget->addTab(serverInfo,tr("서버 정보")); //서버 정보 qdebug() 내용 띄울거임
    ui->tabWidget->addTab(patientInfo, tr("환자정보")); // 환자 정보 검색
    ui->tabWidget->addTab(chatLog, tr("채팅 로그")); // 채팅 로그
}

ServerWindow::~ServerWindow()
{

    delete ui;
}
