#include "chatinvitedform.h"
#include "ui_chatinvitedform.h"

ChatInvitedForm::ChatInvitedForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatInvitedForm)
{
    ui->setupUi(this);
}

ChatInvitedForm::~ChatInvitedForm()
{
    delete ui;
}
