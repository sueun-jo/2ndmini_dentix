#include "patientrepository.h"
#include "patient.h"
#include "jsonfileio.h"  // 공용 JSON 입출력 유틸리티
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QVector>

PatientRepository::PatientRepository() {}

QVector<Patient> PatientRepository::loadAllPatients(const QString& filepath) {
    QVector<Patient> patients;
    QJsonArray arr = JsonFileIO::readJsonArray(filepath);

    for (const QJsonValue& val : arr) {
        patients.append(Patient::fromJson(val.toObject()));
    }
    qDebug() << "[PatientRepository] 불러온 환자 수:" << patients.size();
    return patients;
}

bool PatientRepository::saveAllPatients(const QVector<Patient>& patients, const QString& filepath) {
    QJsonArray arr;
    for (const Patient& p : patients) {
        arr.append(p.toJson());
    }

    return JsonFileIO::writeJsonFile(filepath, arr);
}
