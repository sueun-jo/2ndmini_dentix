#ifndef INVITEDCHATFORM_H
#define INVITEDCHATFORM_H

#include <QWidget>

namespace Ui {
class InvitedChatForm;
}

class InvitedChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit InvitedChatForm(QWidget *parent = nullptr);
    ~InvitedChatForm();

private:
    Ui::InvitedChatForm *ui;
};

#endif // INVITEDCHATFORM_H
