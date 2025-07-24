#ifndef PATIENTINFOCONTROLLER_H
#define PATIENTINFOCONTROLLER_H


#include <QObject>
#include <QVector>
#include <QString>
#include "patientmanager.h"
#include "patient.h"

class PatientInfoController : public QObject
{
    Q_OBJECT

public:

    explicit PatientInfoController(PatientManager* manager, QObject *parent = nullptr);

    // UI에서 호출될 슬롯 (또는 public 메서드)

    void updateAllPatients();

    void searchPatients(const QString& name, const QString& gender,
                        const QString& diagnosis, const QString& treatment);

    bool deletePatient(const QString& name);
    bool modifyPatient(const QJsonObject& newData);

signals:

    void patientsLoaded(const QVector<Patient>& patients);
    void searchCompleted(const QVector<Patient>& results);

private:
    PatientManager* patientManager; // PatientManager 인스턴스에 대한 포인터

};

#endif // PATIENTINFOCONTROLLER_H
