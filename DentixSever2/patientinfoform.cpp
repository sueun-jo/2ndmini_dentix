#include "patientinfoform.h"
#include "ui_patientinfoform.h"

PatientInfoForm::PatientInfoForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientInfoForm)
{
    ui->setupUi(this);

    /*diagnosisComboBox Option*/
    QList<QPair<QString, QString>> diagnosisItems = {
        {"선택 없음", ""},
        {"치아우식증 (충치)", "K02.9"},
        {"신경염 (치수염)", "K04.0"},
        {"치근 염증", "K04.7"},
        {"잇몸병 (치주염)", "K05.3"},
        {"과잉치", "K00.1"},
        {"매복된 치아", "K01.1"},
        {"치아 마모 / 침식", "K03.2"},
        {"잇몸 비대", "K06.1"},
        {"치아 결손 / 상실", "K08.1"},
        {"이갈이 (수면 중)", "G47.63"}
    };
    ui->diagnosisComboBox->clear();
    for (const auto& item : diagnosisItems) {
        ui->diagnosisComboBox->addItem(item.first, item.second);
    }

    /* treatComboBox Option*/
    QList<QPair<QString, QString>> treatmentItems = {
        {"선택 없음", ""},
        {"예방치료", "PREVENT"},
        {"충전치료 (레진/아말감)", "FILLING"},
        {"신경치료 (근관치료)", "RCT"},
        {"발치", "EXTRACTION"},
        {"스케일링", "SCALING"},
        {"잇몸수술 (치주수술)", "PERIO_SURGERY"},
        {"크라운/보철치료", "PROSTHODONTIC"},
        {"임플란트", "IMPLANT"},
        {"교정치료", "ORTHODONTIC"},
        {"나이트가드/이갈이 장치", "BRUXISM_GUARD"}
    };
    ui->treatComboBox->clear();
    for (const auto& item : treatmentItems) {
        ui->treatComboBox->addItem(item.first, item.second);
    }

    /* gender Option */
    QList<QPair<QString, QString>> genderItems = {
        {"선택 없음", ""},
        {"여성", "F"},
        {"남성", "M"}
    };
    ui->genderComboBox->clear();
    for (const auto& item : genderItems){
        ui->genderComboBox->addItem(item.first, item.second);
    }

}

PatientInfoForm::~PatientInfoForm()
{
    ui->diagnosisComboBox->clear();
    ui->treatComboBox->clear();
    ui->genderComboBox->clear();
    delete ui;
}


