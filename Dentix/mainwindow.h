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
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ChatWindow* getChatWindow();
    ChatWindow* chatWindow = nullptr;
private slots:
    void on_patinetInfo_clicked();
    void handleBackFormPatient();
    void on_reservation_clicked();

private:
    Ui::MainWindow *ui;
    PatientWindow* patientWindow = nullptr;



};
#endif // MAINWINDOW_H
