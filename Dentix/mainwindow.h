#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "patientwindow.h"
#include "chatwindow.h"
#include "logincontroller.h"
#include "chatcontroller.h"
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
    void onLoginSuccessful(const QString &userName);

private:
    Ui::MainWindow *ui;
    PatientWindow* patientWindow = nullptr;
    ChatWindow* chatWindow = nullptr;

    Client *client;
    LoginController *loginController;
    ChatController *chatController;
};
#endif // MAINWINDOW_H
