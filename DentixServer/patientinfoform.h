#ifndef PATIENTINFOFORM_H
#define PATIENTINFOFORM_H

#include <QWidget>
#include <QMap>
#include "patientinfocontroller.h"
#include "patient.h"
#include "patientmanager.h"

namespace Ui {
class PatientInfoForm;
}

class PatientInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientInfoForm(PatientManager* manager, QWidget *parent = nullptr);
    ~PatientInfoForm();

private slots:
    void on_pushButton_clicked(); // 검색 버튼 클릭 시
    void updatePatientTable(const QVector<Patient>& patients); // 컨트롤러로부터 환자 목록을 받아 테이블 업데이트

private:
    Ui::PatientInfoForm *ui;
    PatientInfoController* controller; //컨트롤러 객체
    void setupTable(); //테이블 초기 설정

};

#endif // PATIENTINFOFORM_H
