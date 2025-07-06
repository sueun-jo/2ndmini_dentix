#include "chatbasicform.h"
#include "ui_chatbasicform.h"

ChatBasicForm::ChatBasicForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatBasicForm)
{

    ui->setupUi(this);


}

ChatBasicForm::~ChatBasicForm()
{
    delete ui;
}

