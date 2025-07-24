#include "patientaddform.h"
#include "ui_patientaddform.h"
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPixmap>
#include <QLabel>
PatientAddForm::PatientAddForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientAddForm)
{
    ui->setupUi(this);

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

    ui->cbDiagnosisAdd->clear();
    ui->cbDiagnosisAdd->addItems(diagnosisItems);


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
    ui->cbTreatmentAdd->clear();
    ui->cbTreatmentAdd->addItems(treatmentItems);


    /* gender Option */
    QStringList genderItems = {
        "전체",
        "여성",
        "남성",
    };
    ui->cbGenderAdd->clear();
    ui->cbGenderAdd->addItems(genderItems);
}

PatientAddForm::~PatientAddForm()
{
    delete ui;
}

void PatientAddForm::on_btnFileAdd_clicked()
{
    // 1. 이미지 파일 선택
    QString filePath = QFileDialog::getOpenFileName(this, "이미지 선택", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    m_filePath = filePath;
    if (filePath.isEmpty()) {
        qDebug() << "파일 선택 취소됨.";
        return;
    }
    QPixmap pix = filePath;
    ui->lbImageAdd->setPixmap(pix);

}


void PatientAddForm::on_btnSaveAdd_clicked()
{
    QString name = ui->leNameAdd->text();
    QString ageStr = ui->leAgeAdd->text();
    int age = ageStr.toInt();
    QString gender = ui->cbGenderAdd->currentText();
    QString diagnosis = ui->cbDiagnosisAdd->currentText();
    QString treatment = ui->cbTreatmentAdd->currentText();
    QString doctorNote = ui->teDoctorNote->toPlainText();

    emit requestAddPatient(name, age, gender, diagnosis, treatment, doctorNote, m_filePath);
    ui->lbImageAdd->clear();
}




