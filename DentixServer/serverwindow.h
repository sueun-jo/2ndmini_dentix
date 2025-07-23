#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ServerWindow;
}
QT_END_NAMESPACE

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;

private slots:

    void on_actionPatientTab_triggered();
    void on_actionChatLog_triggered();
    void on_actionstartServer_triggered();
    void on_actionstopServer_triggered();
};
#endif // SERVERWINDOW_H
