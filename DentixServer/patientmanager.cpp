#include "patientmanager.h"
#include <QDebug>
#include "logutil.h"
#include "patientsearchfilter.h"

PatientManager::PatientManager() {
    /* patientmanager 생성자에서 repository로부터 json파일 읽어옴 */
    patients = repository.loadAllPatients("patients.json");
    qDebug() <<"[PatientManager] 환자 정보 로드 완료: " << patients.size();
}

bool PatientManager::addPatient(const Patient& patient) {
    patients.append(patient); //vector에 append
    // return repository.saveAllPatients(patients, "patients.json");
    return setAllPatients(patients);
}

// 환자 삭제는 클라이언트에서 특정 환자를 넘기게 돼있으니까 이름을 고유자로 해서 삭제한다
bool PatientManager::deletePatient(const QString& name) {

    for (int i=0; i<patients.size(); i++){
        if (patients[i].getName() == name){
            return setAllPatients(patients);
        }
    }
    return false; //못찾은 경우 false값 반환
}

// 환자 정보 수정도 이름을 기반으로 한다
bool PatientManager::modifyPatient(const QJsonObject& newData){
    QString newName = newData["name"].toString().trimmed();

    for (Patient& p : patients){
        if (p.getName().trimmed() == newName){
            if (newData.contains("diagnosis"))   p.setDiagnosis(newData["diagnosis"].toString());
            if (newData.contains("doctorNote"))  p.setDoctorNote(newData["doctorNote"].toString());
            if (newData.contains("gender"))      p.setGender(newData["gender"].toString());
            if (newData.contains("treatment"))   p.setTreatment(newData["treatment"].toString());
        }
    }
    return setAllPatients(patients);
}



// 다중 조건 검색을 기반으로 한 findPatient 함수
QVector<Patient> PatientManager::findPatient(const PatientSearchFilter& criteria) {
    QVector<Patient> results;

    for (Patient& p : patients) {
        // 이름 필드가 비어있지 않으면, 이름 조건을 만족해야 함
        if (!criteria.name.isEmpty() && !p.getName().contains(criteria.name, Qt::CaseInsensitive))
            continue;

        if (!criteria.gender.isEmpty() && p.getGender() != criteria.gender)
            continue;

        if (!criteria.diagnosis.isEmpty() && criteria.diagnosis != "전체" && p.getDiagnosis() != criteria.diagnosis)
            continue;

        if (!criteria.treatment.isEmpty() && criteria.treatment != "전체" && p.getTreatment() != criteria.treatment)
            continue;

        // 모든 조건을 통과한 환자만 결과에 추가
        results.append(p);
    }
    return results;
}

bool PatientManager::setAllPatients(const QVector<Patient>& updated) {
    patients = updated; //업데이트 된 걸로 patients 갱신
    bool ret = repository.saveAllPatients(patients, "patients.json");
    if (ret){
        qDebug()<<"[PatientManager] 환자 목록 갱신 및 저장 완료. 총 수: " << patients.size();
        return ret;
    } else {
        qDebug()<<"[PatientManager] 환자 목록 저장 실패!";
    }
    return ret;
}

QVector<Patient> PatientManager::getAllPatients() const {
    return patients;
}
