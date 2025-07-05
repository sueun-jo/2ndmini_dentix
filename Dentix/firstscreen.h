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
    explicit FirstScreen(QWidget *parent = nullptr);
    ~FirstScreen();

private slots:
    void on_loginButton_clicked(); //submit버튼 슬롯

private:
    Ui::FirstScreen *ui;

signals:
    void connectToServer(const QString &host, quint16 port);
    void requestLogin(const QString& name, const QString& pw);
};

#endif // FIRSTSCREEN_H
