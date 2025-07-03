#include "patientdeleteform.h"
#include "ui_patientdeleteform.h"

patientDeleteForm::patientDeleteForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientDeleteForm)
{
    ui->setupUi(this);
}

patientDeleteForm::~patientDeleteForm()
{
    delete ui;
}
