#include "patientmanager.h"
#include "patient.h"
#include "patientsearchfilter.h"
#include <QFileDialog>
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
                                    const QString &diagnosis, const QString &treatment, const QString &doctorNote, const QString &filePath)
{

    /*입력된 환자 정보 플로우 */
    //1. 입력한 환자정보 client의 vector에 추가

    QJsonObject dataObj;
    dataObj["name"] = name;
    dataObj["age"] = age;
    dataObj["gender"] = gender;
    dataObj["diagnosis"] = diagnosis;
    dataObj["treatment"] = treatment;
    dataObj["doctorNote"] = doctorNote;


    //2. 백터 업데이트
    Patient patient = Patient::fromJson(dataObj);
    m_patients.append(patient);
    //3. 업데이트 시그널을 각 UI에 보내서 환자정보 업데이트
    emit updateCompleted(m_patients);
    patientinfosendtoserver(dataObj, filePath);
}
//이미지 전송
void PatientManager::patientinfosendtoserver(const QJsonObject &dataObj, const QString &filePath)
{
    QJsonObject jsonObj = dataObj; //요청오면 보낼 json은
    QByteArray imageByteArray;
    QString name = jsonObj.value("name").toString();

    // 2. 파일 오픈 -> QByteArray로 저장
    QFile file(filePath); //QFileDialog로 선택한 파일경로(filePath) open /
    if (file.open(QIODevice::ReadOnly)) {
        imageByteArray = file.readAll();
    }else{
        qDebug() << "파일 열기 실패:" << file.errorString();
        return;
    }

    QString fileName(QString("%1.jpg").arg(name));  //QFileInfo를 통해 받은 이름 QString에 저장
    //QJsonObject는 QJsonValue 타입만 저장 가능하기에 바이트어레이로 저장된 이미지 데이터를 베이스64로 인코딩
    QByteArray base64EncodedData = imageByteArray.toBase64();

    /*파일 이름과 이미지 데이터 환자정보 json에 추가 */
    jsonObj.insert("fileData", QString::fromUtf8(base64EncodedData));
    jsonObj.insert("fileName", fileName);
    QJsonObject reqObj;
    reqObj["type"] = "add";//헤더
    reqObj["data"] = jsonObj;//바디

    QJsonDocument doc(reqObj);

    QByteArray sendData = doc.toJson(); //JsonDocument bytearray로 변환
    qDebug().noquote()<<"[PatientManager] Sending to server: "<< QString::fromUtf8(sendData);

    //시그널
    qDebug()<< "image send"<< QString::fromUtf8(sendData);
    emit sendPatientInfoToServer(sendData);
    file.close();
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
        QJsonObject dataObj;
        dataObj["name"] = name;
      
        QJsonObject reqObj;
        reqObj["type"] = "delete";
        reqObj["data"] = dataObj;


        QJsonDocument doc(reqObj);
        QByteArray sendData = doc.toJson();
        emit deleteRequestToServer(sendData); // AppController로 전송
    } else{
        qDebug() << "[PatientManager] 삭제 실패 : 이름 존재하지 않음." << name;
    }
}

//검색기능
void PatientManager::findPatient(const QString &name, int age, const QString &gender,
                                 const QString &diagnosis, const QString &treatment)
{
    // 검색 필터 구성
    PatientSearchFilter criteria;
    criteria.name = name;
    criteria.age = age;
    criteria.gender = (gender == "전체") ? "" : gender;
    criteria.diagnosis = (diagnosis == "전체") ? "" : diagnosis;
    criteria.treatment = (treatment == "전체") ? "" : treatment;

    QVector<Patient> results;

    for (const Patient& p : m_patients) {
        if (!criteria.name.isEmpty() && !p.getName().contains(criteria.name, Qt::CaseInsensitive))
            continue;   
        if (criteria.age != -1 && p.getAge() != criteria.age)
            continue;
        if (!criteria.gender.isEmpty() && p.getGender() != criteria.gender)
            continue;
        if (!criteria.diagnosis.isEmpty() && p.getDiagnosis() != criteria.diagnosis)
            continue;
        if (!criteria.treatment.isEmpty() && p.getTreatment() != criteria.treatment)
            continue;

        qDebug() << "검색 시작: 이름=" << name << " 나이=" << age;
        results.append(p);
    }

    qDebug() << "[PatientManager] 환자 검색 완료. 검색된 환자 수:" << results.size();
    emit searchCompleted(results);

}




//수정
void PatientManager::modifyPatientData(const QString &newName, int newAge, const QString &newGender,
                                       const QString &newDiagnosis, const QString &newTreatment, const QString &newDoctorNote)
{
    for (Patient &p : m_patients) {
        if (p.getName() == newName) {
            p.setAge(newAge);
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
    dataObj["age"] = newAge;
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
    qDebug().noquote() << "[PatientManager] 수정 요청 전송:" << sendData;
    emit sendPatientInfoToServer(sendData);  // AppController에서 처리

}

