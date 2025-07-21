#include "patientmanager.h"
#include "patient.h"
#include "patientsearchfilter.h"
PatientManager::PatientManager(QObject *parent)
    : QObject(parent)
{
}

//서버로부터 JSON을 받아 임시 저장소에 저장
void PatientManager::updatePatientInfo(const QByteArray &data)
{
    m_patients.clear(); // 기존 임시 저장소 비움

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return;

    QJsonObject root = doc.object();
    QJsonObject dataObj = root.value("data").toObject();
    QJsonArray patientsArray = dataObj.value("patients").toArray();

    for (const QJsonValue &value : patientsArray) {
        QJsonObject patientObj = value.toObject();
        Patient patient = Patient::fromJson(patientObj);
        m_patients.append(patient);
        qDebug() << "환자데이터 받음" << patient.getName();
    }

    // 업데이트 완료 시그널 방출
    emit updateCompleted(m_patients);
}
void PatientManager::addPatientJson(const QString &name, int age, const QString &gender,
                                    const QString &diagnosis, const QString &treatment, const QString &doctorNote)
{

    QString p_name = name;             // 이름
    int p_age = age;                   // 나이
    QString p_gender = gender;         // 성별
    QString p_diagnosis = diagnosis;   // 진단
    QString p_treatment = treatment;   // 치료
    QString p_doctorNote = doctorNote; // 의사 소견

    QJsonObject dataObj;
    dataObj["name"] = p_name;
    dataObj["age"] = p_age;
    dataObj["gender"] = p_gender;
    dataObj["diagnosis"] = p_diagnosis;
    dataObj["treatment"] = p_treatment;
    dataObj["doctorNote"] = p_doctorNote;

    QJsonObject reqObj;
    reqObj["type"] = "add";
    reqObj["data"] = dataObj;

    // 직렬화
    QJsonDocument doc(reqObj);
    QByteArray sendData = doc.toJson();
    qDebug().noquote()<<"[PatientManager] Sending to server: "<< sendData;
    emit sendPatientInfoToServer(sendData);

}
void PatientManager::deletePatientJson(const QString &name)
{

    QString patientName = name;

    // JSON 생성
    QJsonObject reqObj;
    reqObj["type"] = "delete";
    reqObj["name"] = patientName;

    QJsonDocument doc(reqObj);
    QByteArray sendData = doc.toJson();
    emit deleteRequestToServer(sendData); // AppController로 전송
}

void PatientManager::findPatient(const QString &name, const QString &gender,
                                 const QString &diagnosis, const QString &treatment)
{
    // 검색 필터 구성
    PatientSearchFilter criteria;
    criteria.name = name;
    criteria.gender = (gender == "전체") ? "" : gender;
    criteria.diagnosis = (diagnosis == "전체") ? "" : diagnosis;
    criteria.treatment = (treatment == "전체") ? "" : treatment;

    QVector<Patient> results;

    for (const Patient& p : m_patients) {
        if (!criteria.name.isEmpty() && !p.getName().contains(criteria.name, Qt::CaseInsensitive))
            continue;

        if (!criteria.gender.isEmpty() && p.getGender() != criteria.gender)
            continue;

        if (!criteria.diagnosis.isEmpty() && p.getDiagnosis() != criteria.diagnosis)
            continue;

        if (!criteria.treatment.isEmpty() && p.getTreatment() != criteria.treatment)
            continue;

        results.append(p);
    }

    emit searchCompleted(results);
    qDebug() << "[PatientManager] 환자 검색 완료. 검색된 환자 수:" << results.size();
}

