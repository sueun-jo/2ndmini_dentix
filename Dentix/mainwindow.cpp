#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chatWindow = new ChatWindow(this);
}


void MainWindow::on_patinetInfo_clicked()
{
    if(!patientWindow){
        patientWindow = new PatientWindow(this);
        //patient에서 돌아가기 요청이 오면 처리
        connect(patientWindow, &PatientWindow::backToMainWindow, this, &MainWindow::handleBackFormPatient);
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
        chatWindow = new ChatWindow(this);
    }
    chatWindow->show();
}
ChatWindow* MainWindow::getChatWindow() {
    return chatWindow;
}



MainWindow::~MainWindow()
{
    delete ui;
}


