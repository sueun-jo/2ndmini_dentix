#include "chatbasicform.h"
#include "ui_chatbasicform.h"

ChatBasicForm::ChatBasicForm(QWidget *parent, const QString &chatRoomId)
    : QWidget(parent), ui(new Ui::ChatBasicForm), m_chatRoomId(chatRoomId)
{
    ui->setupUi(this);
    connect(ui->leMessageChat, &QLineEdit::returnPressed, ui->btnSendChat, &QPushButton::click);

}

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

void ChatBasicForm::receiveChatData(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QJsonObject dataObj = obj["data"].toObject();

    QString user;
    if (dataObj.contains("sender") && dataObj["sender"].isString()) {
        user = dataObj["sender"].toString();
    } else {
        user = "SYSTEM";
    }
    QString message = dataObj["messageContent"].toString();

    QString logEntry = QString("[%1]: %2").arg(user, message);
    ui->lwLogChat->addItem(logEntry);

    ui->lwLogChat->scrollToTop();

    QStringList onlineUsers;
    QJsonArray nameArray = dataObj["onlineUserNames"].toArray();
    for (const QJsonValue &val : nameArray) {
        onlineUsers.append(val.toString());
    }

    // listWidget UI 업데이트
    ui->listWidget->clear();
    for (const QString &name : onlineUsers) {
        ui->listWidget->addItem(name);
    }
}


void ChatBasicForm::userListUpdate(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QJsonObject dataObj = obj["data"].toObject();


    QStringList onlineUsers;
    QJsonArray nameArray = dataObj["onlineUserNames"].toArray();
    for (const QJsonValue &val : nameArray) {
        onlineUsers.append(val.toString());
    }
    ui->listWidget->clear();
    for (const QString &name : onlineUsers) {
        ui->listWidget->addItem(name);
    }
}
