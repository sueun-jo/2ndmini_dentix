#include "serverinfoform.h"
#include "ui_serverinfoform.h"
#include "server.h"

ServerInfoForm* ServerInfoForm::m_instance = nullptr;

ServerInfoForm::ServerInfoForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerInfoForm)
{
    m_instance = this;
    connect(this, &ServerInfoForm::logMessage, this, &ServerInfoForm::appendLog);
    ui->setupUi(this);

}

ServerInfoForm::~ServerInfoForm(){
    delete ui;
}

void ServerInfoForm::appendLog(const QString& msg){
    ui->serverLog->appendPlainText(msg);
}

// startServerBtn 눌리면 server 시작
void ServerInfoForm::on_startServer_clicked()
{
    Server::getInstance()->startServer(54321);
}

void ServerInfoForm::serverLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    switch (type){
    case QtDebugMsg:
        //콘솔에 띄움
        fprintf(stderr, "Debug: %s\n", qPrintable(msg));
        //시그널 emit
        if (ServerInfoForm::instance())
            emit ServerInfoForm::instance()->logMessage(QString("[Debug] ") + msg);
        break;
    }
}

ServerInfoForm* ServerInfoForm::instance(){
    return m_instance;
}

