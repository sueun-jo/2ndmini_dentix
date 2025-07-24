// PatientInfoController.cpp
#include "patientinfocontroller.h"
#include <QDebug> // 디버깅 메시지 출력을 위해 포함

PatientInfoController::PatientInfoController(PatientManager* manager, QObject *parent)
    : QObject(parent), patientManager(manager) // 멤버 초기화 리스트에서 manager 초기화
{
    // PatientManager가 유효한지 확인
    if (!patientManager) {
        qDebug() << "[PatientInfoController] Error: PatientManager pointer is null!";
    }
}

void PatientInfoController::updateAllPatients() {
    if (patientManager) {
        // PatientManager를 통해 모든 환자 데이터를 가져옴
        QVector<Patient> allPatients = patientManager->getAllPatients();
        // UI에 환자 목록이 로드되었다고 시그널
        emit patientsLoaded(allPatients);
        qDebug() << "[PatientInfoController] 모든 환자 정보 로드 요청 및 UI 업데이트 시그널 발생. 환자 수:" << allPatients.size();
    } else {
        qWarning() << "[PatientInfoController] PatientManager가 없어 loadAllPatients를 수행할 수 없습니다.";
    }
}

void PatientInfoController::searchPatients(const QString& name, const QString& gender,
                                           const QString& diagnosis, const QString& treatment) {
    if (patientManager) {
        // 검색 필터 구조체 값 채우기 from UI
        PatientSearchFilter criteria;
        criteria.name = name;
        // "전체"는 조건 없는거나 마찬가지임
        criteria.gender = (gender == "전체") ? "" : gender;
        criteria.diagnosis = (diagnosis == "전체") ? "" : diagnosis;
        criteria.treatment = (treatment == "전체") ? "" : treatment;

        //검색 수행
        QVector<Patient> results = patientManager->findPatient(criteria);
        //검색 끝나고 signal 발생
        emit searchCompleted(results);
    } else {
        qWarning() << "[PatientInfoController] PatientManager가 없어 searchPatients를 수행할 수 없습니다.";
    }
}

bool PatientInfoController::deletePatient(const QString& name) {
    if (patientManager && patientManager->deletePatient(name)) {
        updateAllPatients();
        return true;
    }
    return false;
}


bool PatientInfoController::modifyPatient(const QJsonObject& newData){
    if (patientManager && patientManager->modifyPatient(newData)){
        updateAllPatients();
        return true;
    }
    return false;
}
