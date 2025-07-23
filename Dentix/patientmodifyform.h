#ifndef PATIENTMODIFYFORM_H
#define PATIENTMODIFYFORM_H

#include <QWidget>
#include <QVector>
#include <QListWidget>
#include "patient.h"
class Patient;
namespace Ui {
class PatientModifyForm;
}

class PatientModifyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientModifyForm(QWidget *parent = nullptr);
    ~PatientModifyForm();

signals:
    void requestSearchPatient(const QString &name, int age, const QString &gender,
                              const QString &diagnosis, const QString &treatment);
    void requestModifyUpdate(const QString &newName, int age, const QString &newGender,
                      const QString &newDiagnosis, const QString &newTreatment, const QString &newDoctorNote);
public slots:

    void updatePatientList(const QVector<Patient> &newPatients);
    void updatePatientInfo(const QVector<Patient> &newPatients);
    void on_btnSearchModify_clicked();

private slots:

    void on_lwListModify_itemDoubleClicked(QListWidgetItem *item);

    void on_btnSaveModify_clicked();

private:
    Ui::PatientModifyForm *ui;
    QVector<Patient> Patients;
};

#endif // PATIENTMODIFYFORM_H
