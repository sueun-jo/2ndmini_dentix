#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>

namespace Ui {
class chatForm;
}

class chatForm : public QWidget
{
    Q_OBJECT

public:
    explicit chatForm(QWidget *parent = nullptr);
    ~chatForm();
private:
    void on_pushButton_clicked();
private:
    Ui::chatForm *ui;
};

#endif // CHATFORM_H
