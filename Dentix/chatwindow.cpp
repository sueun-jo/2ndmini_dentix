#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatbasicform.h"
#include <QTabBar>
#include "chatgroupform.h"
#include "chatinvitedform.h"
ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    ui->tabWidget->tabBar()->hide();

    connect(ui->actionMainChat, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(0);
    });
    connect(ui->actionGroupChat, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(1);
    });
    connect(ui->actionInvitedChat, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(2);
    });
    ChatBasicForm* chat = new ChatBasicForm(this);
    ui->tabWidget->addTab(chat, tr("고객 정보"));  // index 0

    ChatGroupForm* groupchat = new ChatGroupForm(this);
    ui->tabWidget->addTab(groupchat, tr("그룹채팅")); // index 1

    ChatInvitedForm* invitedchat = new ChatInvitedForm(this);
    ui->tabWidget->addTab(invitedchat, tr("그룹채팅")); // index 2


    ui->tabWidget->setCurrentIndex(0);  // 처음 보여줄 탭 설정
}

ChatWindow::~ChatWindow()
{
    delete ui;
}









