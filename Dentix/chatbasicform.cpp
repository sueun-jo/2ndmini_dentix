#include "chatbasicform.h"
#include "ui_chatbasicform.h"
ChatBasicForm::ChatBasicForm(QWidget *parent, const QString &chatRoomId)
    : QWidget(parent), ui(new Ui::ChatBasicForm), m_chatRoomId(chatRoomId)
{ ui->setupUi(this); }

ChatBasicForm::~ChatBasicForm()
{ delete ui; }


void ChatBasicForm::on_btnSendChat_clicked()
{
    //leMessageChat->라인에딧의 메세지 텍스트 message에 저장
    QString message = ui->leMessageChat->text().trimmed();
    qDebug()<<"[전체채팅] : send Message Data"<< message;
    emit sendMessageSubmit(message, m_chatRoomId);
    //메시지 전송 후 입력창 비우기
    ui->leMessageChat->clear();
}
