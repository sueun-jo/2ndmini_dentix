#include "chatinvitedform.h"
#include "ui_chatinvitedform.h"

ChatInvitedForm::ChatInvitedForm(QWidget *parent, const QString &chatRoomId)
    : QWidget(parent), ui(new Ui::ChatInvitedForm), m_chatRoomId(chatRoomId)
{
    ui->setupUi(this);
}
ChatInvitedForm::~ChatInvitedForm(){
    delete ui;
}
void ChatInvitedForm::on_btnSendInvited_clicked(){
    //leMessageChat->라인에딧의 메세지 텍스트 message에 저장
    QString message = ui->leMessageInvited->text().trimmed();
    qDebug()<<"[초대된 채팅] : send Message Data"<< message;
    emit sendMessageSubmit(message, m_chatRoomId);
    //메시지 전송 후 입력창 비우기
    ui->leMessageInvited->clear();
}
