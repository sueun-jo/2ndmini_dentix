#ifndef PATIENTINFOFORM_H
#define PATIENTINFOFORM_H

#include <QWidget>

namespace Ui {
class PatientInfoForm;
}

class PatientInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientInfoForm(QWidget *parent = nullptr);
    ~PatientInfoForm();

private slots:


private:
    Ui::PatientInfoForm *ui;
    QMap<QString, QString> diagnosisCodeMap;
};

#endif // PATIENTINFOFORM_H
