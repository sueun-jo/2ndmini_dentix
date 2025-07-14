#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_patientwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client(this);
    loginController = new LoginController(client, this);
    chatController = new ChatController(client, this);

    connect(loginController, &LoginController::loginSuccess, this, &MainWindow::onLoginSuccessful);

}

MainWindow::~MainWindow()
{
    delete ui;
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





void MainWindow::onLoginSuccessful(const QString &userName)
{
    chatController->setUserName(userName);
}


