#include "patientsearchform.h"
#include "ui_patientsearchform.h"
#include <QPixmap>
patientSearchForm::patientSearchForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientSearchForm)
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
}

patientSearchForm::~patientSearchForm()
{
    delete ui;
}
