#ifndef PATIENTDELETEFORM_H
#define PATIENTDELETEFORM_H

#include <QWidget>
#include <QVector>
#include "patient.h"
class Patient;
namespace Ui {
class patientDeleteForm;
}

class PatientDeleteForm : public QWidget
{
    Q_OBJECT
signals:
    void deleteRequest(const QString &name);
    void requestSearchPatient(const QString &name, const QString &gender,
                           const QString &diagnosis, const QString &treatment);
    void deletePatientByName(const QString &name);
public:
    explicit PatientDeleteForm(QWidget *parent = nullptr);

    void updatePatientTable(const QVector<Patient> &patientList);
    void onDeleteButtonClicked();

private slots:
    void on_btnSearchDelete_clicked();

private:
    Ui::patientDeleteForm *ui;
    QVector<Patient> Patients;
};

#endif // PATIENTDELETEFORM_H
