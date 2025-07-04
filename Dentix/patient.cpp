#include "patient.h"
#include "qtabbar.h"
#include "ui_patient.h"
#include "patientsearchform.h"
#include "patientaddform.h"
#include "patientdeleteform.h"
#include "patientmodifyform.h"

patient::patient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::patient)
{
    //ui->tabWidget->tabBar()->hide();

    ui->setupUi(this);

    ui->tabWidget->tabBar()->hide();

    connect(ui->actionSearch, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(0);
    });

    connect(ui->actionAdd, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(1);
    });
    connect(ui->actionModify, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(2);
    });
    connect(ui->actionDelete, &QAction::triggered, this, [=]() {
        ui->tabWidget->setCurrentIndex(3);
    });

    patientSearchForm* patientSearch  = new patientSearchForm(this);
    ui->tabWidget->addTab(patientSearch, tr("고객 정보"));  // index 0

    patientAddForm* patientAdd  = new patientAddForm(this);
    ui->tabWidget->addTab(patientAdd, tr("고객 정보"));  // index 1

    PatientModifyForm* PatientModify = new PatientModifyForm(this);
    ui->tabWidget->addTab(PatientModify, tr("그룹채팅")); // index 2

    patientDeleteForm* patientDelete = new patientDeleteForm(this);
    ui->tabWidget->addTab(patientDelete, tr("그룹채팅")); // index 2

    ui->tabWidget->setCurrentIndex(0);  // 처음 보여줄 탭 설정
}

patient::~patient()
{
    delete ui;
}




