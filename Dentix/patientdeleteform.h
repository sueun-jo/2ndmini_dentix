#ifndef PATIENTDELETEFORM_H
#define PATIENTDELETEFORM_H

#include <QWidget>

namespace Ui {
class patientDeleteForm;
}

class patientDeleteForm : public QWidget
{
    Q_OBJECT

public:
    explicit patientDeleteForm(QWidget *parent = nullptr);
    ~patientDeleteForm();

private:
    Ui::patientDeleteForm *ui;
};

#endif // PATIENTDELETEFORM_H
