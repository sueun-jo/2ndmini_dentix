#include "chatgroupform.h"
#include "ui_chatgroupform.h"

ChatGroupForm::ChatGroupForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatGroupForm)
{
    ui->setupUi(this);
}

ChatGroupForm::~ChatGroupForm()
{
    delete ui;
}
