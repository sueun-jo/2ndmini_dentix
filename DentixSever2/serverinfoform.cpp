#include "serverinfoform.h"
#include "ui_serverinfoform.h"

ServerInfoForm::ServerInfoForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerInfoForm)
{
    ui->setupUi(this);
}

ServerInfoForm::~ServerInfoForm()
{
    delete ui;
}
