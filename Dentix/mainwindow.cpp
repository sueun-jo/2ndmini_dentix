#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // chatWindow = new ChatWindow(this);
    // patientWindow = new PatientWindow(this);
}


void MainWindow::on_reservation_clicked()
{

    emit requestUserList();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_patinetInfo_clicked()
{
    qDebug()<<"clicked patient btn";
    emit requestPatientInfo();
}

