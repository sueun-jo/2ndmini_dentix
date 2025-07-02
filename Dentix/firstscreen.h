#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

#include "client.h"
#include "mainwindow.h"

namespace Ui {
class FirstScreen;
}

class FirstScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstScreen(Client* client, QWidget *parent = nullptr);
    ~FirstScreen();

private slots:
    void on_submitButton_clicked(); //submit버튼 슬롯

private:
    Ui::FirstScreen *ui;
    Client* client; //서버 통신용 client 포인터
};

#endif // FIRSTSCREEN_H
