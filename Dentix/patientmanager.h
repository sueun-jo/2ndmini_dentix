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
public:
    explicit PatientManager(QObject *parent = nullptr);

public slots:
    void addPatientJson(const QString &name, int age, const QString &gender,
                        const QString &diagnosis, const QString &treatment, const QString &doctorNote);
    void updatePatientInfo(const QByteArray &data);
    void deletePatientJson(const QString &name);
    void findPatient(const QString &name, const QString &gender,
                           const QString &diagnosis, const QString &treatment);

private:
    QVector<Patient> m_patients;
};

#endif // PATIENTMANAGER_H

