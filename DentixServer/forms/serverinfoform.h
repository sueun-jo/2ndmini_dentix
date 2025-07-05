#ifndef SERVERINFOFORM_H
#define SERVERINFOFORM_H

#include <QWidget>

namespace Ui {
class ServerInfoForm;
}

class ServerInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit ServerInfoForm(QWidget *parent = nullptr);
    ~ServerInfoForm();

private:
    Ui::ServerInfoForm *ui;

public slots:
    void appendLog(const QString& msg);
private slots:
    void on_startServer_clicked();
};

#endif // SERVERINFOFORM_H
