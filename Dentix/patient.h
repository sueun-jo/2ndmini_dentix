#ifndef PATIENT_H
#define PATIENT_H

#include <QMainWindow>
namespace Ui {
class patient;
}

class patient : public QMainWindow
{
    Q_OBJECT

public:
    explicit patient(QWidget *parent = nullptr);
    ~patient();

signals:
    void backToMainWindow();

private slots:
    void on_actionBack_triggered();//돌아가기 액션 트리거 생성

private:
    Ui::patient *ui;
};

#endif // PATIENT_H
