#ifndef CHATGROUPFORM_H
#define CHATGROUPFORM_H

#include <QWidget>

namespace Ui {
class ChatGroupForm;
}

class ChatGroupForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatGroupForm(QWidget *parent = nullptr);
    ~ChatGroupForm();

private:
    Ui::ChatGroupForm *ui;
};

#endif // CHATGROUPFORM_H
