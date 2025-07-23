#include "serverinfoform.h"
#include "ui_serverinfoform.h"
#include "server.h"

#include <QThread>
#include <QTimer>

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

    if (!logWorker) {
        logWorker = new ChatLogWorker;
        logThread = new QThread;
        logWorker->moveToThread(logThread);
        logThread->start();

        connect(this, &ServerInfoForm::requestSaveChats, logWorker, &ChatLogWorker::saveChats);
        connect(logWorker, &ChatLogWorker::saveDone, this, []() {
            qDebug() << "[logWorker]채팅 로그 저장 완료✅";
        });
    }

    if (!autoSaveTimer) {
        autoSaveTimer = new QTimer(this);
        connect(autoSaveTimer, &QTimer::timeout, this, [this]() {
            // 실제 저장 데이터 얻어서 emit
            auto chatManager = Server::getInstance()->getChatManager();
            auto chats = chatManager->getChats();
            emit requestSaveChats(chats, "chatlog.json");
            qDebug() << "[Timer] ⏰자동 저장 요청";
        });
        autoSaveTimer->start(30000);
    }

}

void ServerInfoForm::on_stopServer_clicked()
{
    shutdownServer();
}

void ServerInfoForm::serverLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    switch (type){
    case QtDebugMsg:
        //콘솔에 띄움
        fprintf(stderr, "Debug: %s\n", qPrintable(msg));
        //시그널 emit
        if (ServerInfoForm::instance())
            emit ServerInfoForm::instance()->logMessage(msg);
        break;
    }
}

ServerInfoForm* ServerInfoForm::instance(){
    return m_instance;
}


void ServerInfoForm::shutdownServer()
{
    Server::getInstance()->stopServer();

    if (autoSaveTimer) {
        autoSaveTimer->stop();
        delete autoSaveTimer;
        autoSaveTimer = nullptr;
    }

    if (logThread) {
        logThread->quit();
        logThread->wait();
        delete logWorker;
        delete logThread;
        logWorker = nullptr;
        logThread = nullptr;
    }
}
