#include "patientsearchform.h"
#include "ui_patientsearchform.h"
#include <QPixmap>
#include <QTableWidgetItem>
#include <QHeaderView>
PatientSearchForm::PatientSearchForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientSearchForm)
{
    ui->setupUi(this);
    QImage img("image/test.png");
    if (!img.isNull()) {
        img = img.convertToFormat(QImage::Format_RGB32); // 알파 채널 제거
        QSize labelSize = ui->lbImageSearch->size();
        QPixmap pixmap = QPixmap::fromImage(img.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->lbImageSearch->setPixmap(pixmap);
        ui->lbImageSearch->setScaledContents(false); // 비율 유지
    }
    QStringList headers = { "이름", "나이", "성별", "진단", "치료" };
    ui->twInfoSearch->setColumnCount(headers.size());
    ui->twInfoSearch->setHorizontalHeaderLabels(headers);
    ui->twInfoSearch->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twInfoSearch->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twInfoSearch->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

    ui->cbDiagnosisSearch->clear();
    ui->cbDiagnosisSearch->addItems(diagnosisItems);


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
    ui->cbTreatmentSearch->clear();
    ui->cbTreatmentSearch->addItems(treatmentItems);


    /* gender Option */
    QStringList genderItems = {
        "전체",
        "여성",
        "남성",
    };
    ui->cbGenderSearch->clear();
    ui->cbGenderSearch->addItems(genderItems);


    connect(ui->lwListSearch, &QListWidget::itemDoubleClicked,
            this, &PatientSearchForm::on_lwListSearch_itemDoubleClicked);
}

//유저리스트
void PatientSearchForm::updatePatientList(const QVector<Patient> &newPatients)
{
    Patients = newPatients;  // 내부 저장소 갱신

    // 리스트 초기화
    ui->lwListSearch->clear();  // listWidget은 UI에서 만든 QListWidget

    // 이름만 출력
    for (const Patient &p : Patients) {
        ui->lwListSearch->addItem(p.getName());
    }
}

// void PatientSearchForm::updatePatientTable(const QVector<Patient> &newPatients)
// {
//     Patients = newPatients;  // 내부 저장소 갱신

//     // 테이블 초기화
//     ui->twInfoSearch->clearContents();
//     ui->twInfoSearch->setRowCount(0);


//     // 데이터 출력
//     for (int i = 0; i < Patients.size(); ++i) {
//         const Patient &p = Patients[i];
//         ui->twInfoSearch->insertRow(i);
//         ui->twInfoSearch->setItem(i, 0, new QTableWidgetItem(p.getName()));
//         ui->twInfoSearch->setItem(i, 1, new QTableWidgetItem(QString::number(p.getAge())));
//         ui->twInfoSearch->setItem(i, 2, new QTableWidgetItem(p.getGender()));
//         ui->twInfoSearch->setItem(i, 3, new QTableWidgetItem(p.getDiagnosis()));
//         ui->twInfoSearch->setItem(i, 4, new QTableWidgetItem(p.getTreatment()));

//     }
// }



//Manager에 검색요청
PatientSearchForm::~PatientSearchForm()
{
    delete ui;
}

void PatientSearchForm::on_btnSearahSearch_clicked()
{
    QString name = ui->leNameSearch->text();
    QString gender = ui->cbGenderSearch->currentText();
    QString diagnosis = ui->cbDiagnosisSearch->currentText();
    QString treatment = ui->cbTreatmentSearch->currentText();

    //매니저에 검색 요청 -> connect patient manager
    emit requestSearchPatient(name, gender, diagnosis, treatment);
}


void PatientSearchForm::on_lwListSearch_itemDoubleClicked(QListWidgetItem *item)
{
    QString selectedName = item->text();  // 리스트에서 선택된 이름

    for (const Patient &p : Patients) {
        if (p.getName() == selectedName) {
            // 테이블 위젯 갱신
            ui->twInfoSearch->clearContents();
            ui->twInfoSearch->setRowCount(1);  // 하나만 표시
            ui->twInfoSearch->setItem(0, 0, new QTableWidgetItem(p.getName()));
            ui->twInfoSearch->setItem(0, 1, new QTableWidgetItem(QString::number(p.getAge())));
            ui->twInfoSearch->setItem(0, 2, new QTableWidgetItem(p.getGender()));
            ui->twInfoSearch->setItem(0, 3, new QTableWidgetItem(p.getDiagnosis()));
            ui->twInfoSearch->setItem(0, 4, new QTableWidgetItem(p.getTreatment()));

            // 닥터 노트 텍스트 위젯 갱신
            ui->teDoctorNote->clear();
            ui->teDoctorNote->setText(p.getDoctorNote());
            break;
        }
    }
}

