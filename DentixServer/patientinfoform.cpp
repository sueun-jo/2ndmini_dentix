#include "patientinfoform.h"
#include "ui_patientinfoform.h"

PatientInfoForm::PatientInfoForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientInfoForm)
{
    ui->setupUi(this);

    /*diagnosisComboBox Option*/
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

    ui->diagnosisComboBox->clear();
    ui->diagnosisComboBox->addItems(diagnosisItems);


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
    ui->treatComboBox->clear();
    ui->treatComboBox->addItems(treatmentItems);


    /* gender Option */
    QStringList genderItems = {
        "전체",
        "여성",
        "남성",
    };
    ui->genderComboBox->clear();
    ui->genderComboBox->addItems(genderItems);


}

PatientInfoForm::~PatientInfoForm()
{
    ui->diagnosisComboBox->clear();
    ui->treatComboBox->clear();
    ui->genderComboBox->clear();
    delete ui;
}


