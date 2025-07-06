#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_patient.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_patinetInfo_clicked()
{
    if(!patientWindow){
        patientWindow = new patient(this);
        //patient에서 돌아가기 요청이 오면 처리
        connect(patientWindow, &patient::backToMainWindow, this, &MainWindow::handleBackFormPatient);
    }
    patientWindow->show();
    this->hide();

}


void MainWindow::handleBackFormPatient()
{
    this->show();
}

void MainWindow::on_reservation_clicked()
{
    if(!chatWindow){
        chatWindow = new chatPage(this);
    }
    chatWindow->show();
}

