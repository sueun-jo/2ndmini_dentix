#include "patientwindow.h"
#include "qtabbar.h"
#include "ui_patientwindow.h"
#include "patientsearchform.h"
#include "patientaddform.h"
#include "patientdeleteform.h"
#include "patientmodifyform.h"
#include <QTabBar>
PatientWindow::PatientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PatientWindow)
{

    ui->setupUi(this);
    /*툴바 위젯 눌렀을 때 엑션 연결 Qt designer 사용 x 코드로 직접 연결 */
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
}


void PatientWindow::setPatientTap(PatientSearchForm* searchForm, PatientAddForm* addForm,PatientDeleteForm* deleteForm,PatientModifyForm* modifyForm)
{
    if (!searchForm || !addForm || !modifyForm || !deleteForm ) return;

    ui->tabWidget->clear();

    ui->tabWidget->addTab(searchForm, tr("고객정보검색"));  // index 0

    ui->tabWidget->addTab(addForm, tr("고객정보추가"));  // index 1

    ui->tabWidget->addTab(modifyForm, tr("고객정보수정")); // index 2

    ui->tabWidget->addTab(deleteForm, tr("고객정보삭제")); // index 2

    ui->tabWidget->setCurrentIndex(0);  // 처음 보여줄 탭 설정
}

PatientWindow::~PatientWindow()
{
    delete ui;
}


void PatientWindow::on_actionBack_triggered()//백투 윈도우 시그널-->
{
    emit backToMainWindow();
}

