#include "chatPage.h"
#include "ui_chatPage.h"
#include "chatform.h"
#include <QTabBar>
#include "groupchatform.h"
#include "invitedchatform.h"
chatPage::chatPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chatPage)
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
    chatForm* chat = new chatForm(this);
    ui->tabWidget->addTab(chat, tr("고객 정보"));  // index 0

    GroupChatForm* groupchat = new GroupChatForm(this);
    ui->tabWidget->addTab(groupchat, tr("그룹채팅")); // index 1

    InvitedChatForm* invitedchat = new InvitedChatForm(this);
    ui->tabWidget->addTab(invitedchat, tr("그룹채팅")); // index 2


    ui->tabWidget->setCurrentIndex(0);  // 처음 보여줄 탭 설정
}

chatPage::~chatPage()
{
    delete ui;
}









