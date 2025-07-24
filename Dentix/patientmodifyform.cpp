#include "patientmodifyform.h"
#include "ui_patientmodifyform.h"
#include <QPixmap>
#include <QTableWidgetItem>
#include <QHeaderView>
PatientModifyForm::PatientModifyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientModifyForm)
{
    ui->setupUi(this);
    QImage img("image/test.png");
    if (!img.isNull()) {
        img = img.convertToFormat(QImage::Format_RGB32); // 알파 채널 제거
        QSize labelSize = ui->lbImageModify->size();
        QPixmap pixmap = QPixmap::fromImage(img.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->lbImageModify->setPixmap(pixmap);
        ui->lbImageModify->setScaledContents(false); // 비율 유지
    }
    QStringList headers = { "이름", "나이", "성별", "진단", "치료" };
    ui->twInfoModify->setColumnCount(headers.size());
    ui->twInfoModify->setHorizontalHeaderLabels(headers);
    ui->twInfoModify->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twInfoModify->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twInfoModify->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

    ui->cbDiagnosisModify->clear();
    ui->cbDiagnosisModify->addItems(diagnosisItems);


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
    ui->cbTreatmentModify->clear();
    ui->cbTreatmentModify->addItems(treatmentItems);


    /* gender Option */
    QStringList genderItems = {
        "전체",
        "여성",
        "남성",
    };
    ui->cbGenderModify->clear();
    ui->cbGenderModify->addItems(genderItems);



}

PatientModifyForm::~PatientModifyForm()
{
    delete ui;
}


void PatientModifyForm::updatePatientList(const QVector<Patient> &newPatients)
{
    Patients = newPatients;  // 내부 저장소 갱신

    // 리스트 초기화
    ui->lwListModify->clear();  // listWidget은 UI에서 만든 QListWidget

    // 이름만 출력
    for (const Patient &p : Patients) {
        ui->lwListModify->addItem(p.getName());
    }
}

void PatientModifyForm::on_btnSearchModify_clicked()
{
    QString name = ui->leNameModify->text();
    int age = -1;
    if (!ui->leAgeModify->text().trimmed().isEmpty()) {
        age = ui->leAgeModify->text().toInt();
    }
    QString gender = ui->cbGenderModify->currentText();
    QString diagnosis = ui->cbDiagnosisModify->currentText();
    QString treatment = ui->cbTreatmentModify->currentText();

    //매니저에 검색 요청 -> connect patient manager
    emit requestSearchPatient(name, age, gender, diagnosis, treatment);
}


void PatientModifyForm::on_lwListModify_itemDoubleClicked(QListWidgetItem *item)
{
    QString selectedName = item->text();  // 리스트에서 선택된 이름

    for (const Patient &p : Patients) {
        if (p.getName() == selectedName) {
            // 테이블 위젯 갱신
            ui->twInfoModify->clearContents();
            ui->twInfoModify->setRowCount(1);  // 하나만 표시
            ui->twInfoModify->setItem(0, 0, new QTableWidgetItem(p.getName()));
            ui->twInfoModify->setItem(0, 1, new QTableWidgetItem(QString::number(p.getAge())));
            ui->twInfoModify->setItem(0, 2, new QTableWidgetItem(p.getGender()));
            ui->twInfoModify->setItem(0, 3, new QTableWidgetItem(p.getDiagnosis()));
            ui->twInfoModify->setItem(0, 4, new QTableWidgetItem(p.getTreatment()));

            // 닥터 노트 텍스트 위젯 갱신
            ui->teDoctorNote->clear();
            ui->teDoctorNote->setText(p.getDoctorNote());

            ui->cbGenderModify->setCurrentText(p.getGender());
            ui->cbDiagnosisModify->setCurrentText(p.getDiagnosis());
            ui->cbTreatmentModify->setCurrentText(p.getTreatment());
            ui->leNameModify->setText(p.getName());
            ui->teDoctorNote->setText(p.getDoctorNote());

            break;

            QJsonObject data;
            data["name"] = p.getName();

            QJsonObject imageData;
            imageData["type"] = "requestPatientImage";
            imageData["data"] = data;
            QJsonDocument doc(imageData);
            QByteArray sendData = doc.toJson();

            qDebug().noquote() << "[PatientModify] 요청 전송: " << sendData;
            emit requestImageToServer_modify(sendData);
            break;
        }
    }
}
void PatientModifyForm::imageShowTest_modify(const QByteArray &imageData)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(imageData, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[Server] Invalid JSON received!";
        return;
    }
    QJsonObject root = doc.object();
    QString type = root["for"].toString();
    if (type != "requestPatientImage") return;

    QJsonObject data = root["data"].toObject();
    QString fileDataBase64 = data["image"].toString();
    QByteArray imageBinary = QByteArray::fromBase64(fileDataBase64.toUtf8());


    QImage paitentImage;
    paitentImage.loadFromData(imageBinary);
    if (paitentImage.isNull()) {
        qDebug() << "QImage 로딩 실패";
    } else {
        QPixmap pix = QPixmap::fromImage(paitentImage);
        ui->lbImageModify->setPixmap(pix.scaled(ui->lbImageModify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}


void PatientModifyForm::updatePatientInfo(const QVector<Patient> &newPatients)
{
    Patients = newPatients;  // 내부 저장소 갱신

    // 리스트 초기화
    ui->lwListModify->clear();  // 이름 리스트 초기화

    for (const Patient &p : Patients) {
        // 리스트에 이름만 추가
        ui->lwListModify->addItem(p.getName());
    }

    // 만약 Patients[0]의 정보를 초기 표시하려면 아래처럼 설정
    if (!Patients.isEmpty()) {
        const Patient &first = Patients.first();
        ui->leAgeModify->setText(QString::number(first.getAge()));
        ui->cbGenderModify->setCurrentText(first.getGender());
        ui->cbDiagnosisModify->setCurrentText(first.getDiagnosis());
        ui->cbTreatmentModify->setCurrentText(first.getTreatment());
        ui->leNameModify->setText(first.getName());
        ui->teDoctorNote->setText(first.getDoctorNote());
    }
}



void PatientModifyForm::on_btnSaveModify_clicked()
{
    if (Patients.isEmpty()) return;
    QString newName = ui->leNameModify->text();
    int newAge = ui->leAgeModify->text().toInt();
    QString newGender = ui->cbGenderModify->currentText();
    QString newDiagnosis = ui->cbDiagnosisModify->currentText();
    QString newTreatment = ui->cbTreatmentModify->currentText();
    QString newDoctorNote = ui->teDoctorNote->toPlainText();

    emit requestModifyUpdate(newName, newAge, newGender,newDiagnosis, newTreatment, newDoctorNote);
}

