#include "chatlog.h"
#include "ui_chatlog.h"

ChatLog::ChatLog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatLog)
{
    ui->setupUi(this);
}

ChatLog::~ChatLog()
{
    delete ui;
}

void ChatLog::on_logList_itemClicked(QListWidgetItem *item)
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

