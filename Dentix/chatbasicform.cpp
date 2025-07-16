#include "chatbasicform.h"
#include "ui_chatbasicform.h"
ChatBasicForm::ChatBasicForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatBasicForm)
{
    ui->setupUi(this);
}

ChatBasicForm::~ChatBasicForm()
{
    delete ui;
}


//userName 가져와야함

void ChatBasicForm::on_btnSendChat_clicked()
{
    //leMessageChat->라인에딧의 메세지 텍스트 message에 저장
    QString message = ui->leMessageChat->text().trimmed();
    //message -> chatcontroller
    //chatcontroller->requestMessage(message)
    //직접호출 하지 않고 시그널 발생으로 결합도를 낮춤
    emit sendMessageData(message);
    //메시지 전송 후 입력창 비우기
    ui->leMessageChat->clear();
}
// void ChatBasicForm::sendMessageData(const QString &message){
//     qDebug()<<"sendMessageData *^^*"<< message;
// }
