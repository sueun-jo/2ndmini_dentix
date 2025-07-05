#include "serverinfoform.h"
#include "ui_serverinfoform.h"
#include "server.h"

ServerInfoForm::ServerInfoForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerInfoForm)
{
    ui->setupUi(this);
}

ServerInfoForm::~ServerInfoForm(){
    delete ui;
}

void ServerInfoForm::appendLog(const QString& msg){
    //not implemented yet
    // serverLog->appendPlainText(msg);
}

// startServerBtn 눌리면 server 시작
void ServerInfoForm::on_startServer_clicked()
{
    Server::getInstance()->startServer(54321);
}

