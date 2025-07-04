#include "patient.h"
#include "qtabbar.h"
#include "ui_patient.h"
#include "patientsearchform.h"
patient::patient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::patient)
{
    //ui->tabWidget->tabBar()->hide();

    ui->setupUi(this);
}

patient::~patient()
{
    delete ui;
}

void patient::on_actionAdd_triggered()
{

    patientSearchForm* patientSearch = new patientSearchForm(this);
    ui->tabWidget->addTab(patientSearch, tr("고객 정보"));
}

