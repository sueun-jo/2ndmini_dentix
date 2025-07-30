#include "chatlogform.h"
#include "chat.h"
#include "chatrepository.h"
#include "server.h"
#include "chatlogworker.h"

#include <QDebug>
#include <QPlainTextEdit>
#include <QThread>


ChatLogForm::ChatLogForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatLogForm)
{
    //update용 주석
    ui->setupUi(this);
    logLayout = new QVBoxLayout(ui->logArea);
    ui->logArea->setLayout(logLayout);

    connect(Server::getInstance()->getChatManager(), &ChatManager::chatAdded, this, &ChatLogForm::appendChat);


}

ChatLogForm::~ChatLogForm()
{
    delete ui;
}

void ChatLogForm::on_logList_itemClicked(QListWidgetItem *item)
{
    QString name = item->text();
    ui->chatTitle->setText(name + tr("의 채팅 로그")); // QLabel 업데이트

    QPlainTextEdit * logText = nullptr;

    //logMap에 해당 로그창 있는지 확인
    if (logMap.contains(name)){
        logText = logMap[name];
    } else {
        //새 로그창 생성
        logText = new QPlainTextEdit;
        logText->setReadOnly(true);
        logMap[name] = logText;
        logLayout->addWidget(logText);
    }

    //모든 로그창 숨기고 선택한 로그창만 보여주기

    for (auto* edit : std::as_const(logMap)){
        edit->setVisible(false);
    }
    logText->setVisible(true);
}


void ChatLogForm::on_saveButton_clicked()
{

    // ChatRepository::saveAllChats(allChats, filepath);
    ChatManager* chatManager = Server::getInstance()->getChatManager();
    const QVector<Chat*>& chats = chatManager->getChats();
    QString filepath = "chatlog.json";
    qDebug() << "저장 버튼 눌렀어요!";
    emit requestSaveChats(chats, filepath);
}


void ChatLogForm::on_test_clicked()
{
    ChatManager* chatManager = Server::getInstance()->getChatManager();
    Chat* dummy = new Chat("testuser", "전체채팅", "this is test message");
    chatManager->addChat(dummy);
}

void ChatLogForm::appendChat(Chat* chat){
    if (!chat) return;

    QString key = chat->getChatRoomID(); //chatRoomID가

    QPlainTextEdit* logText = nullptr;

    if (logMap.contains(key)){
        logText = logMap[key];
    } else {
        logText = new QPlainTextEdit;
        logText->setReadOnly(true);
        logText->setStyleSheet("background: white;");
        logMap[key] = logText;
        logLayout->addWidget(logText);
        logText->setVisible(false); // 기본은 숨김
    }

    logText->appendPlainText(chat->toString());

    //현재 선택된 유저/방과 맞으면 보여주기
    QListWidgetItem *currentItem = ui->logList->currentItem();
    if (currentItem && currentItem->text() == key) {
        for (auto* edit : std::as_const(logMap)) edit->setVisible(false);
        logText->setVisible(true);
    }
}
