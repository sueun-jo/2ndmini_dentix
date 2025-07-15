#include "chatlogform.h"
#include "chat.h"
#include "server.h"
#include <QDebug>

ChatLogForm::ChatLogForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatLogForm)
{
    ui->setupUi(this);
    connect(chatManager, &ChatManager::chatAdded, this, &ChatLogForm::appendChat);
}

ChatLogForm::~ChatLogForm()
{
    delete ui;
}

void ChatLogForm::on_logList_itemClicked(QListWidgetItem *item)
{
    QString name = item->text();
    ui->chatTitle->setText(name + tr("의 채팅 로그")); // QLabel 업데이트

    // 기존 페이지 있는지 확인
    for (int i = 0; i < ui->logStacked->count(); i++) {
        QWidget *page = ui->logStacked->widget(i);
        if (page->objectName() == name) {
            ui->logStacked->setCurrentWidget(page);
            return;
        }
    }

    // 새 페이지 생성
    QWidget *newPage = new QWidget;
    newPage->setObjectName(name);

    QVBoxLayout *layout = new QVBoxLayout(newPage);
    QPlainTextEdit *logText = new QPlainTextEdit;

    layout->addWidget(logText);
    newPage->setLayout(layout);

    ui->logStacked->addWidget(newPage);
    ui->logStacked->setCurrentWidget(newPage);
}


void ChatLogForm::on_saveButton_clicked()
{

}


void ChatLogForm::on_test_clicked()
{
    ChatManager* chatManager = Server::getInstance()->getChatManager();
    Chat* dummy = new Chat("testuser", "test-all", "this is test message");
    chatManager->addChat(dummy);
}

void ChatLogForm::appendChat(Chat* chat){
    if (!chat) return;

}
