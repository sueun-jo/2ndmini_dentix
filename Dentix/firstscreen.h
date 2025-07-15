#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

#include "client.h"
#include "logincontroller.h"
class MainWindow;
class LoginController;

namespace Ui {
class FirstScreen;
}

class FirstScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstScreen(QWidget *parent = nullptr);
    ~FirstScreen();

public slots:
    void handleLoginSuccess(const QString& userName);
    void handleLoginFailed(const QString& reason);

private slots:
    void on_loginButton_clicked(); //submit버튼 슬롯

private:
    Ui::FirstScreen *ui;
    //controller가 Model과 View를 관리하므로 FirstScreen은 Controller만 알면 됨
    LoginController *loginController;
    Client *client; //조립을 위해 잠시 소유
    MainWindow *mainWindow;

signals:
    //View는 Controller에게 요청만 보냄
    void loginRequest(const QString& name, const QString& pw);
};

#endif // FIRSTSCREEN_H
