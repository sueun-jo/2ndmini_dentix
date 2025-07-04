#ifndef PATIENTADDFORM_H
#define PATIENTADDFORM_H

#include <QWidget>

namespace Ui {
class patientAddForm;
}

class patientAddForm : public QWidget
{
    Q_OBJECT

public:
    explicit patientAddForm(QWidget *parent = nullptr);
    ~patientAddForm();

private:
    Ui::patientAddForm *ui;
};

#endif // PATIENTADDFORM_H
