#include "patientmanager.h"
#include "patient.h"
#include "patientsearchfilter.h"
PatientManager::PatientManager(QObject *parent)
    : QObject(parent)
{
}

//서버로부터 JSON을 받아 백터에 저장
void PatientManager::updatePatientInfo(const QByteArray &data)
{
    m_patients.clear();

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
void PatientManager::addPatientData(const QString &name, int age, const QString &gender,
                                    const QString &diagnosis, const QString &treatment, const QString &doctorNote)
{


    QJsonObject dataObj;
    dataObj["name"] = name;
    dataObj["age"] = age;
    dataObj["gender"] = gender;
    dataObj["diagnosis"] = diagnosis;
    dataObj["treatment"] = treatment;
    dataObj["doctorNote"] = doctorNote;

    QJsonObject reqObj;
    reqObj["type"] = "add";
    reqObj["data"] = dataObj;

    //백터 업데이트
    Patient patient = Patient::fromJson(dataObj);
    m_patients.append(patient);

    //서버 전송
    QJsonDocument doc(reqObj);
    QByteArray sendData = doc.toJson();
    qDebug().noquote()<<"[PatientManager] Sending to server: "<< sendData;
    emit sendPatientInfoToServer(sendData);


    emit updateCompleted(m_patients);


}

//삭제기능
void PatientManager::deletePatientData(const QString &name)
{
    bool found = false; //
    for (int i = 0; i < m_patients.size(); ++i) {
        if (m_patients[i].getName() == name) {
            m_patients.removeAt(i);
            found = true;
            break; // 이름이 같은 환자가 여럿일 경우 하나만 삭제
        }
    }
    //모든 view에 연결
    //updatePatientTable 함수에 연결
    if(found){
        emit updateCompleted(m_patients);

        // JSON 생성
        QJsonObject reqObj;
        reqObj["type"] = "delete";
        reqObj["name"] = name;

        QJsonDocument doc(reqObj);
        QByteArray sendData = doc.toJson();
        emit deleteRequestToServer(sendData); // AppController로 전송
    } else{
        qDebug() << "[PatientManager] 삭제 실패 : 이름 존재하지 않음." << name;
    }

}
//검색기능
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





void PatientManager::modifyPatientData(const QString &newName, const QString &newGender,
                                       const QString &newDiagnosis, const QString &newTreatment, const QString &newDoctorNote)
{
    for (Patient &p : m_patients) {
        if (p.getName() == newName) {
            p.setGender(newGender);
            p.setDiagnosis(newDiagnosis);
            p.setTreatment(newTreatment);
            p.setDoctorNote(newDoctorNote);
            break;
        }
    }

    emit updateCompleted(m_patients);

    QJsonObject dataObj;
    dataObj["name"] = newName;
    dataObj["gender"] = newGender;
    dataObj["diagnosis"] = newDiagnosis;
    dataObj["treatment"] = newTreatment;
    dataObj["doctorNote"] = newDoctorNote;

    QJsonObject reqObj;
    reqObj["type"] = "modify";
    reqObj["data"] = dataObj;

    // 4. 서버 전송
    QJsonDocument doc(reqObj);
    QByteArray sendData = doc.toJson();
    emit sendPatientInfoToServer(sendData);  // AppController에서 처리
    qDebug().noquote() << "[PatientManager] 수정 요청 전송:" << sendData;
}

