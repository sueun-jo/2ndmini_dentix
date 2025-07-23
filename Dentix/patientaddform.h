#ifndef PATIENTADDFORM_H
#define PATIENTADDFORM_H

#include <QWidget>

namespace Ui {
class PatientAddForm;
}

class PatientAddForm : public QWidget
{
    Q_OBJECT
signals:
    void requestAddPatient(const QString &name, int age, const QString &gender,
                              const QString &diagnosis, const QString &treatment, const QString doctorNote);
    void sendImageHeader(const QByteArray &headerData);  // AppController에서 연결

    void sendImageData(const QByteArray chunk);
public:
    explicit PatientAddForm(QWidget *parent = nullptr);
    ~PatientAddForm();

private slots:
    void on_btnSaveAdd_clicked();

    void on_btnFileAdd_clicked();

private:
    Ui::PatientAddForm *ui;
    QString filePath;
};

#endif // PATIENTADDFORM_H
