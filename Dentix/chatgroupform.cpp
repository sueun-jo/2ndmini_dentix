#include "chatgroupform.h"
#include "ui_chatgroupform.h"

ChatGroupForm::ChatGroupForm(QWidget *parent, const QString &chatRoomId)
    : QWidget(parent), ui(new Ui::ChatGroupForm) ,m_chatRoomId(chatRoomId)
{ ui->setupUi(this); }

ChatGroupForm::~ChatGroupForm()
{ delete ui; }

void ChatGroupForm::on_btnSendGroup_clicked()
{
    //leMessageChat->라인에딧의 메세지 텍스트 message에 저장
    QString message = ui->leMessageGroup->text().trimmed();
    qDebug()<<"[그룹 채팅] : send Message Data"<< message;
    emit sendMessageSubmit(message, m_chatRoomId);
    //메시지 전송 후 입력창 비우기
    ui->leMessageGroup->clear();
}

