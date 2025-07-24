#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "patient.h"
#include "patientrepository.h"
#include "patientsearchfilter.h"
#include <QVector>
#include <QString>
#include <QTcpSocket>

class PatientManager {
public:
    PatientManager();

    bool addPatient(const Patient& patient);                 // 환자 추가
    bool deletePatient(const QString& name);                 // 환자 삭제
    bool modifyPatient(const QJsonObject& newData);          // 환자 수정
    QJsonObject sendPatientImage(const QString& name);              // 환자 사진 정보 보내기

    QVector<Patient> findPatient(const PatientSearchFilter& criteria);   // 조건으로 환자 찾기
    QVector<Patient> getAllPatients() const;              // 전체 목록 반환
    bool setAllPatients(const QVector<Patient>& updated); // 환자 정보 수정사항 update

private:
    QVector<Patient> patients;                // 메모리 상 환자 목록
    PatientRepository repository;             // JSON 입출력 도우미
};

#endif // PATIENTMANAGER_H
