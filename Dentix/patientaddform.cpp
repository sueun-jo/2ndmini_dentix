#include "patientaddform.h"
#include "ui_patientaddform.h"

patientAddForm::patientAddForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientAddForm)
{
    ui->setupUi(this);
}

patientAddForm::~patientAddForm()
{
    delete ui;
}
