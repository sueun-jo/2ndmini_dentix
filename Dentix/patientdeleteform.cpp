#include "patientdeleteform.h"
#include "ui_patientdeleteform.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include "patientmanager.h"
PatientDeleteForm::PatientDeleteForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientDeleteForm)
{
    ui->setupUi(this);
    //InfoTable 초기 설정
    QStringList headers = {"이름", "나이", "성별", "진단", "치료" };
    ui->twInfoDelete->setColumnCount(headers.size());
    ui->twInfoDelete->setHorizontalHeaderLabels(headers);
    ui->twInfoDelete->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twInfoDelete->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twInfoDelete->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList diagnosisItems = {
        "전체",
        "치아우식증 (충치)",
        "신경염 (치수염)",
        "치근 염증",
        "잇몸병 (치주염)",
        "과잉치",
        "매복된 치아",
        "치아 마모 / 침식",
        "잇몸 비대",
        "치아 결손 / 상실",
        "이갈이 (수면 중)"
    };

    ui->cbDiagnosisDelete->clear();
    ui->cbDiagnosisDelete->addItems(diagnosisItems);


    /* treatComboBox Option*/
    QStringList treatmentItems = {
        "전체",
        "예방치료",
        "충전치료 (레진/아말감)",
        "신경치료 (근관치료)",
        "발치",
        "스케일링",
        "잇몸수술 (치주수술)",
        "크라운/보철치료",
        "임플란트",
        "교정치료",
        "나이트가드/이갈이 장치"
    };
    ui->cbTreatmentDelete->clear();
    ui->cbTreatmentDelete->addItems(treatmentItems);


    /* gender Option */
    QStringList genderItems = {
        "전체",
        "여성",
        "남성",
    };
    ui->cbGenderDelete->clear();
    ui->cbGenderDelete->addItems(genderItems);

    connect(ui->btnDelete, &QPushButton::clicked, this, &PatientDeleteForm::onDeleteButtonClicked);

}

//초기 화면 및 검색결과 출력
void PatientDeleteForm::updatePatientTable(const QVector<Patient> &newPatients)
{
    Patients = newPatients;  // 내부 저장소 갱신

    // 테이블 초기화
    ui->twInfoDelete->clearContents();
    ui->twInfoDelete->setRowCount(0);


    // 데이터 출력
    for (int i = 0; i < Patients.size(); ++i) {
        const Patient &p = Patients[i];
        ui->twInfoDelete->insertRow(i);
        ui->twInfoDelete->setItem(i, 0, new QTableWidgetItem(p.getName()));
        ui->twInfoDelete->setItem(i, 1, new QTableWidgetItem(QString::number(p.getAge())));
        ui->twInfoDelete->setItem(i, 2, new QTableWidgetItem(p.getGender()));
        ui->twInfoDelete->setItem(i, 3, new QTableWidgetItem(p.getDiagnosis()));
        ui->twInfoDelete->setItem(i, 4, new QTableWidgetItem(p.getTreatment()));

    }
}


void PatientDeleteForm::onDeleteButtonClicked()
{
    int row=ui->twInfoDelete->currentRow();
    if(row<0){
        QMessageBox::warning(this, "선택오류", "삭제할 환자 선택");
        return;
    }

    QString name = ui->twInfoDelete->item(row, 0)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "삭제 확인",
                                  QString("정말로 '%1' 환자를 삭제하시겠습니까?").arg(name),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit deleteRequest(name);
        deletePatientByName(name);
    }
}



void PatientDeleteForm::on_btnSearchDelete_clicked()
{
    QString name = ui->leNameDelete->text();
    int age = -1;
    if (!ui->leAgeDelete->text().trimmed().isEmpty()) {
        age = ui->leAgeDelete->text().toInt();
    }
    QString gender = ui->cbGenderDelete->currentText();
    QString diagnosis = ui->cbDiagnosisDelete->currentText();
    QString treatment = ui->cbTreatmentDelete->currentText();

    //매니저에 검색 요청 -> connect patient manager
    emit requestSearchPatient(name, age, gender, diagnosis, treatment);
}

