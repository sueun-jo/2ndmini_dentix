#ifndef GROUPCHATFORM_H
#define GROUPCHATFORM_H

#include <QWidget>

namespace Ui {
class GroupChatForm;
}

class GroupChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChatForm(QWidget *parent = nullptr);
    ~GroupChatForm();

private:
    Ui::GroupChatForm *ui;
};

#endif // GROUPCHATFORM_H
