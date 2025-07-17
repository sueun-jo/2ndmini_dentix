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

//로그인 성공시 logincontroller에서 날라오는 mainwindow에서 받자
void MainWindow::receiveUserName(const QString &userName)
{
    qDebug() << "MainWindow: receivedUserName 슬롯 호출됨, 받은 값:" << userName;
    if(!userName.isEmpty()){
        qDebug()<<"No User nameData :";
    }
    qDebug()<<"recive userName: "<< userName;
}



MainWindow::~MainWindow()
{
    delete ui;
}


