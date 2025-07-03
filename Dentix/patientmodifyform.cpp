#include "patientmodifyform.h"
#include "ui_patientmodifyform.h"

PatientModifyForm::PatientModifyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientModifyForm)
{
    ui->setupUi(this);
}

PatientModifyForm::~PatientModifyForm()
{
    delete ui;
}
