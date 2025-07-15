#ifndef PATIENTINFOCONTROLLER_H
#define PATIENTINFOCONTROLLER_H


#include <QObject>
#include <QVector>
#include <QString> // QString을 사용하므로 포함
#include "patientmanager.h" // PatientManager 포함
#include "patient.h" // Patient 클래스 포함

class PatientInfoController : public QObject
{
    Q_OBJECT // Qt의 시그널/슬롯 메커니즘을 사용하기 위해 필요

public:

    explicit PatientInfoController(PatientManager* manager, QObject *parent = nullptr);

    // UI에서 호출될 슬롯 (또는 public 메서드)

    void loadAllPatients();

    void searchPatients(const QString& name, const QString& gender,
                        const QString& diagnosis, const QString& treatment);

signals:

    void patientsLoaded(const QVector<Patient>& patients);
    void searchCompleted(const QVector<Patient>& results);

private:
    PatientManager* patientManager; // PatientManager 인스턴스에 대한 포인터

};

#endif // PATIENTINFOCONTROLLER_H
