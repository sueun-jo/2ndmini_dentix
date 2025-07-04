#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
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
    secondWindow = new patient();
    secondWindow->show();
    this->hide();

}

