#include "chatpopup.h"
#include "ui_chatpopup.h"

chatPopUp::chatPopUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatPopUp)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);  // 출력용으로 사용 시 추천
}

chatPopUp::~chatPopUp()
{
    delete ui;
}

void chatPopUp::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();

    if (!input.isEmpty()) {
        ui->textEdit->append("[나] " + input);
        ui->lineEdit->clear();
    }
}
