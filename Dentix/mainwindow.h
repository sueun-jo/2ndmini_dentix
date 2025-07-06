#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "patient.h"
#include "chatPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_patinetInfo_clicked();
    void handleBackFormPatient();

    void on_reservation_clicked();

private:
    Ui::MainWindow *ui;
    patient* patientWindow = nullptr;
    chatPage* chatWindow = nullptr;

};
#endif // MAINWINDOW_H
