#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatbasicform.h"
// #include "chatgroupform.h"
// #include "chatinvitedform.h"
#include <QTabBar>

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();

    connect(ui->actionMainChat, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(0);
    });
    // connect(ui->actionGroupChat, &QAction::triggered, this, [=]() {
    //     ui->tabWidget->setCurrentIndex(1);
    // });
    // connect(ui->actionInvitedChat, &QAction::triggered, this, [=]() {
    //     ui->tabWidget->setCurrentIndex(2);
    // });
}

void ChatWindow::setChatTabs(ChatBasicForm* basic)
{

    ui->tabWidget->clear();  // 기존 탭 제거

    ui->tabWidget->addTab(basic, tr("기본 채팅"));    // index 0
    // ui->tabWidget->addTab(group, tr("그룹 채팅"));    // index 1
    // ui->tabWidget->addTab(invited, tr("초대 채팅"));  // index 2

    ui->tabWidget->setCurrentIndex(0);  // 기본 채팅 탭 보여주기
}

ChatWindow::~ChatWindow()
{delete ui;}
