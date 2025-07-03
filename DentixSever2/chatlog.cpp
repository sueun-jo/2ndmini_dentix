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
