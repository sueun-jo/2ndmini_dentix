#include "groupchatform.h"
#include "ui_groupchatform.h"

GroupChatForm::GroupChatForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GroupChatForm)
{
    ui->setupUi(this);
}

GroupChatForm::~GroupChatForm()
{
    delete ui;
}
