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
    dataObj["filePath"] = filePath;


    //2. 백터 업데이트
    Patient patient = Patient::fromJson(dataObj);
    m_patients.append(patient);
    //3. 업데이트 시그널을 각 UI에 보내서 환자정보 업데이트
    emit updateCompleted(m_patients);


    /* 환자 리스트 add 업데이트 이후 추가한 환자정보와 파일 서버로 보내기 위한 로직 시작*/

    //1. addform.cpp 에서 넘겨준 파일경로의 파일 오픈
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "파일 열기 실패:" << file.errorString();
        return;
    }
    //2. 열린 파일에 대한 메타데이터
    QFileInfo info(file);
    QString fileName = info.fileName();
    qint64 fileSize = info.size();
    const int chunkSize = 4096;
    int totalChunks = qCeil(static_cast<double>(fileSize) / chunkSize);
    int chunkIndex = 0;

    //3. 환자정보 저장 플로우에서 활용된 jsonObject에 파일정보 추가
    dataObj.insert("filename", fileName);
    dataObj.insert("fileSize", fileSize);

    //4. json Document 설정
    QJsonObject reqObj;
    reqObj["type"] = "add"; //헤더
    reqObj["data"] = dataObj;//바디
    QJsonDocument doc(reqObj);

    // 5. json Document를 바이트어래이로 변환
    QByteArray sendData = doc.toJson();

    //6. 서버로 전송
    qDebug().noquote()<<"[PatientManager] Sending to server: "<< QString::fromUtf8(sendData);
    emit sendPatientInfoToServer(sendData);

    // QJsonObject header;
    // header["type"] = "fileUpload";
    // header["fileName"] = fileName;
    // header["fileSize"] = fileSize;
    // header["totalChunks"] = totalChunks;


    //7. 패킷 분할로 보내기 위해 분할전송마다 구분될 전송데이터 info 설정 및 전송ㅇ
    while (!file.atEnd()) {
        QByteArray chunk = file.read(4096);

        QJsonObject wrapper;
        wrapper["type"] = "fileChunk";
        wrapper["fileName"] = fileName;
        wrapper["chunkIndex"] = chunkIndex;
        wrapper["totalChunks"] = totalChunks;
        wrapper["chunkStart"] = (chunkIndex == 0);
        wrapper["chunkEnd"] = (chunkIndex == totalChunks - 1);
        wrapper["chunkSize"] = chunk.size();

        QJsonDocument doc(wrapper);
        QByteArray headerJson = doc.toJson(QJsonDocument::Compact) + '\n';

        qDebug() << "[PatientManager] Sending image file: " << fileName << ", size: " << fileSize;
        emit sendImageData(headerJson);
        emit sendImageData(chunk);     // 서버로 데이터 청크 전송

        chunkIndex++;
    }
    //8. 파일전송 완료되면 close
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
        if (!criteria.imagePath.isEmpty() && p.getImagePath() != criteria.imagePath)
            continue;
        qDebug() << "검색 시작: 이름=" << name << " 나이=" << age;
        results.append(p);
    }

    qDebug() << "[PatientManager] 환자 검색 완료. 검색된 환자 수:" << results.size();
    emit searchCompleted(results);

}





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

