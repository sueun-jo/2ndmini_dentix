#ifndef PATIENTSEARCHFORM_H
#define PATIENTSEARCHFORM_H

#include <QWidget>

namespace Ui {
class patientSearchForm;
}

class patientSearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit patientSearchForm(QWidget *parent = nullptr);
    ~patientSearchForm();

private:
    Ui::patientSearchForm *ui;
};

#endif // PATIENTSEARCHFORM_H
