#include "serverwindow.h"
#include "ui_serverwindow.h"

#include "serverinfoform.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    ServerInfoForm* serverInfo = new ServerInfoForm(this);
    ui->tabWidget->addTab(serverInfo,tr("서버 정보")); //서버 정보
    ui->tabWidget->addTab(); // 환자 정보
    ui->tabWidget->addTab(); // 채팅로그

}

ServerWindow::~ServerWindow()
{
    delete ui;
}
