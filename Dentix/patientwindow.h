#ifndef PATIENT_H
#define PATIENT_H

#include <QMainWindow>


class PatientSearchForm;
class PatientAddForm;
class PatientDeleteForm;
class PatientModifyForm;

namespace Ui {
class PatientWindow;
class PatientSearchForm;
class PatientAddForm;
class PatientDeleteForm;
class PatientModifyForm;
}

class PatientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatientWindow(QWidget *parent = nullptr);
    ~PatientWindow();
    void setPatientTap(PatientSearchForm* searchForm, PatientAddForm* addForm,PatientDeleteForm* deleteForm,PatientModifyForm* modifyForm);

signals:
    void backToMainWindow();

private slots:
    void on_actionBack_triggered();//돌아가기 액션 트리거 생성


private:
    Ui::PatientWindow *ui;
};

#endif // PATIENT_H
