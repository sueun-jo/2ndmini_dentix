#include "patientsearchform.h"
#include "ui_patientsearchform.h"

patientSearchForm::patientSearchForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientSearchForm)
{
    ui->setupUi(this);
}

patientSearchForm::~patientSearchForm()
{
    delete ui;
}
