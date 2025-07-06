#include "invitedchatform.h"
#include "ui_invitedchatform.h"

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
