#ifndef PATIENT_H
#define PATIENT_H

#include <QMainWindow>

namespace Ui {
class patient;
}

class patient : public QMainWindow
{
    Q_OBJECT

public:
    explicit patient(QWidget *parent = nullptr);
    ~patient();

private slots:
    void on_actionAdd_triggered();

private:
    Ui::patient *ui;
};

#endif // PATIENT_H
