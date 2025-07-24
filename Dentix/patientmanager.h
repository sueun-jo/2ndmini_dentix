#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "patient.h"
class Patient;
class PatientManager : public QObject
{
    Q_OBJECT

signals:
    void updateCompleted(const QVector<Patient> &newPatients);
    void deleteRequestToServer(const QByteArray &JsonData);
    void searchCompleted(const QVector<Patient> &result);
    void sendPatientInfoToServer(const QByteArray &sendData);
    void sendImageData(const QByteArray &chunk);

    /*추가될 시그널 (미완성)*/
public:
    explicit PatientManager(QObject *parent = nullptr);
    const QVector<Patient>& getPatientList() const {return m_patients;};
public slots:
    void modifyPatientData(const QString &newName, int newAge, const QString &newGender,
                           const QString &newDiagnosis, const QString &newTreatment, const QString &newDoctorNote);
    void updatePatientInfo(const QByteArray &data);
    void deletePatientData(const QString &name);
    void patientinfosendtoserver(const QJsonObject &dataObj, const QString &filePath);
    void findPatient(const QString &name, int age, const QString &gender,
                           const QString &diagnosis, const QString &treatment);
    void addPatientData(const QString &name, int age, const QString &gender,
                       const QString &diagnosis, const QString &treatment, const QString &doctorNote, const QString &filePath);
private:
       QVector<Patient> m_patients;
};

#endif // PATIENTMANAGER_H

