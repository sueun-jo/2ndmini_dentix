#ifndef CHATBASICFORM_H
#define CHATBASICFORM_H

#include <QWidget>

namespace Ui {
class ChatBasicForm;
}

class ChatBasicForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBasicForm(QWidget *parent = nullptr);
    ~ChatBasicForm();
private:
    void on_pushButton_clicked();
private:
    Ui::ChatBasicForm *ui;
};

#endif // CHATBASICFORM_H
