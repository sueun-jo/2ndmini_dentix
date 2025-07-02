#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class patientWindow;
}

class patientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit patientWindow(QWidget *parent = nullptr);
    ~patientWindow();

private:
    Ui::patientWindow *ui;
};

#endif // PATIENTWINDOW_H
