#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

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

private:
    Ui::FirstScreen *ui;

private slots:
    void submit_clicked();
};

#endif // FIRSTSCREEN_H
