#include "patientsearchform.h"
#include "ui_patientsearchform.h"
#include <QPixmap>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLabel>
#include <QFile>
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





PatientSearchForm::~PatientSearchForm()
{
    delete ui;
}
//Manager에 검색요청

void PatientSearchForm::on_btnSearahSearch_clicked()
{
    QString name = ui->leNameSearch->text();
    int age = -1;
    if (!ui->leAgeSearch->text().trimmed().isEmpty()) {
        age = ui->leAgeSearch->text().toInt();
    }
    QString gender = ui->cbGenderSearch->currentText();
    QString diagnosis = ui->cbDiagnosisSearch->currentText();
    QString treatment = ui->cbTreatmentSearch->currentText();

    //매니저에 검색 요청 -> connect patient manager
    emit requestSearchPatient(name, age, gender, diagnosis, treatment);
}


void PatientSearchForm::on_lwListSearch_itemDoubleClicked(QListWidgetItem *item)
{


    ui->lbImageSearch->clear();


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

            // QPixmap pix(p.getImagePath());

            // if (!pix.isNull()) {
            //     ui->lbImageSearch->setPixmap(pix.scaled(ui->lbImageSearch->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // } else {
            //     qDebug() << "이미지를 불러올 수 없습니다:" << p.getImagePath();
            // }

            /*현재는 로컬이미지를 띄우는 형식으로 되어있음 하지만 이후에 서버에서 데이터 받아와서 띄우는 형식으로 수정 예정*/
            //이미지 요청 시그널 추가
            //아래 코드는 보내는 시그널 요청 형식

            QJsonObject data;
            data["name"] = p.getName();

            QJsonObject imageData;
            imageData["type"] = "requestPatientImage";
            imageData["data"] = data;
            QJsonDocument doc(imageData);
            QByteArray sendData = doc.toJson();

            qDebug().noquote() << "[PatientSearchForm] 요청 전송: " << sendData;
            emit requestImageToServer(sendData);
            break;
        }
    }
}

void PatientSearchForm::imageShowTest(const QByteArray &imageData)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(imageData, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[Server] Invalid JSON received!";
        return;
    }
    // QJsonObject root = doc.object();
    // QString type = root["type"].toString();
    // if (type != "add") return;
    QJsonObject root = doc.object();
    QString type = root["for"].toString();
    if (type != "requestPatientImage") return;
    QJsonObject data = root["data"].toObject();
    // 1. 이미지 추출
    //QString name = data["name"].toString();
    QString fileDataBase64 = data["fileData"].toString();
    // 3. 이미지 저장: Base64 디코딩
    QByteArray imageBinary = QByteArray::fromBase64(fileDataBase64.toUtf8());
    // QFile imageFile(QStringLiteral("images/%1_image.jpg").arg(name));
    // if (!imageFile.open(QIODevice::WriteOnly)) {
    //     qWarning()<<"test 이미지 저장 실패" << imageFile.errorString();
    // }else {
    //     imageFile.write(imageBinary);
    //     imageFile.close();
    // }
    // QString imagePath = QString("images/%1_image.jpg").arg(name);
    QPixmap pix;
    if (!pix.loadFromData(imageBinary)) {
        qWarning() << "이미지를 불러올 수 없습니다: Base64 디코딩 후 이미지 생성 실패";
        return;
    }
    if (!pix.isNull()) {
        ui->lbImageSearch->setPixmap(pix.scaled(ui->lbImageSearch->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "이미지를 불러올 수 없습니다:";
    }
 //   qDebug() << "[Server] 저장 완료:" << name;
}
