#include "patientinfoform.h"
#include "ui_patientinfoform.h"

PatientInfoForm::PatientInfoForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientInfoForm)
{
    ui->setupUi(this);

    QStringList diagnosisList = {
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
    ui->diagnosisComboBox->addItems(diagnosisList);

    diagnosisCodeMap = {
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
}

PatientInfoForm::~PatientInfoForm()
{
    delete ui;
}


