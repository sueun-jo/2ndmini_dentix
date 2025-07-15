#include "patientinfoform.h"
#include "ui_patientinfoform.h"

PatientInfoForm::PatientInfoForm(PatientManager* manager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientInfoForm)
    , controller(new PatientInfoController(manager, this))
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

    if (this->controller){
        connect(this->controller, &PatientInfoController::patientsLoaded,
                this, &PatientInfoForm::updatePatientTable);
        connect(this->controller, &PatientInfoController::searchCompleted,
                this, &PatientInfoForm::updatePatientTable);

        // 폼이 로드될 때 모든 환자 정보 요청
        this->controller->loadAllPatients();
    } else {
        qWarning() << "[PatientInfoForm] Controller is null!";
    }
    connect(ui->pushButton, &QPushButton::clicked, this, &PatientInfoForm::on_pushButton_clicked);
}

PatientInfoForm::~PatientInfoForm()
{
    ui->diagnosisComboBox->clear();
    ui->treatComboBox->clear();
    ui->genderComboBox->clear();
    delete ui;
    delete controller;
}


void PatientInfoForm::on_pushButton_clicked()
{
    // UI에서 검색 조건 가져오기
    QString name = ui->lineEdit->text();
    QString gender = ui->genderComboBox->currentText();
    QString diagnosis = ui->diagnosisComboBox->currentText();
    QString treatment = ui->treatComboBox->currentText();

    // 컨트롤러에 검색 요청
    if (controller) {
        controller->searchPatients(name, gender, diagnosis, treatment);
    }
}

void PatientInfoForm::updatePatientTable(const QVector<Patient>& patients) {
    ui->tableWidget->setRowCount(0); // 기존 내용 지우기

    for (int i = 0; i < patients.size(); ++i) {
        const Patient& p = patients.at(i);
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(p.getName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(p.getAge())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(p.getGender()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(p.getDiagnosis()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(p.getTreatment()));
    }
    qDebug() << "[PatientInfoForm] 테이블 업데이트 완료. 표시된 환자 수:" << patients.size();
}
