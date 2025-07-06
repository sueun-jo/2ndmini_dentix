#include "chatbasicform.h"
#include "ui_chatbasicform.h"

ChatBasicForm::ChatBasicForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatBasicForm)
{

    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);  // 출력용으로 사용 시 추천

}

ChatBasicForm::~ChatBasicForm()
{
    delete ui;
}

void ChatBasicForm::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();

    if (!input.isEmpty()) {
        ui->textEdit->append("[나] " + input);
        ui->lineEdit->clear();
    }

}
