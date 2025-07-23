#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "patientwindow.h"
#include "chatwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void requestPatientInfo();
    void requestUserList();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleBackFormPatient();
private slots:
    void on_reservation_clicked();
    void on_patinetInfo_clicked();

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
