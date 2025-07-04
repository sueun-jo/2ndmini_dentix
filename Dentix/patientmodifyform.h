#ifndef PATIENTMODIFYFORM_H
#define PATIENTMODIFYFORM_H

#include <QWidget>

namespace Ui {
class PatientModifyForm;
}

class PatientModifyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientModifyForm(QWidget *parent = nullptr);
    ~PatientModifyForm();

private:
    Ui::PatientModifyForm *ui;
};

#endif // PATIENTMODIFYFORM_H
