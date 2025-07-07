#ifndef PATIENTREPOSITORY_H
#define PATIENTREPOSITORY_H
#include "patient.h"

class PatientRepository
{
public:
    PatientRepository();
    QVector<Patient> loadAllPatients(const QString& filepath);
    bool saveAllPatients(const QVector<Patient>& patients, const QString& filepath);
};

#endif // PATIENTREPOSITORY_H
