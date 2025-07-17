#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {

class MainWindow;
class FirstScreen;
}

class FirstScreen: public QMainWindow
{
    Q_OBJECT
signals:
    //View는 Controller에게 요청만 보냄
    void loginRequest(const QString& name, const QString& pw);
    void connectServerRequest(const QString &host, quint16 port);
public:
    explicit FirstScreen(QWidget *parent = nullptr);
    ~FirstScreen();

public slots:

private slots:
    void on_loginButton_clicked(); //submit버튼 슬롯

private:
    Ui::FirstScreen *ui;

};

#endif // FIRSTSCREEN_H
