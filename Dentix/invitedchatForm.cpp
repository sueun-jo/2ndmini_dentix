#include "invitedchatForm.h"
#include "ui_invitedchatForm.h"

InvitedChatForm::InvitedChatForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InvitedChatForm)
{
    ui->setupUi(this);
}

InvitedChatForm::~InvitedChatForm()
{
    delete ui;
}
