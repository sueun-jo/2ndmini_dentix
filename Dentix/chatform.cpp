#include "chatform.h"
#include "ui_chatform.h"

chatForm::chatForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatForm)
{

    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);  // 출력용으로 사용 시 추천

}

chatForm::~chatForm()
{
    delete ui;
}

void chatForm::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();

    if (!input.isEmpty()) {
        ui->textEdit->append("[나] " + input);
        ui->lineEdit->clear();
    }

}
