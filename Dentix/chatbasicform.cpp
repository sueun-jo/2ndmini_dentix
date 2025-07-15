#include "chatbasicform.h"
#include "ui_chatbasicform.h"
#include "chatcontroller.h"
ChatBasicForm::ChatBasicForm(ChatController *chatController, QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatBasicForm) , m_chatController(chatController)
{

    ui->setupUi(this);
    //requestMessage시그널 Controller의 슬롯에 연결 : 결합도 낮추기
    connect(this, &ChatBasicForm::requestMessage, chatController, &ChatController::requestMessage);
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
    emit requestMessage(message);
    //메시지 전송 후 입력창 비우기
    ui->leMessageChat->clear();
}

