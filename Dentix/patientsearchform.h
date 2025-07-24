#ifndef PATIENTSEARCHFORM_H
#define PATIENTSEARCHFORM_H

#include <QWidget>
#include <QVector>
#include <QListWidget>
#include "patient.h"
class Patient;
namespace Ui {
class PatientSearchForm;
}

class PatientSearchForm : public QWidget
{
    Q_OBJECT
signals:
    void requestImageToServer(const QByteArray &sendData);
    void requestSearchPatient(const QString &name, int age, const QString &gender,
                              const QString &diagnosis, const QString &treatment);
public:
    explicit PatientSearchForm(QWidget *parent = nullptr);
    ~PatientSearchForm();
public slots:
    void on_btnSearahSearch_clicked();
    void updatePatientList(const QVector<Patient> &newPatients);

    void imageShowTest(const QByteArray &imageData);//테스트용 지울예정
private slots:
    void on_lwListSearch_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::PatientSearchForm *ui;
    QVector<Patient> Patients;
};

#endif // PATIENTSEARCHFORM_Hupd
