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
};

#endif // SERVERINFOFORM_H
