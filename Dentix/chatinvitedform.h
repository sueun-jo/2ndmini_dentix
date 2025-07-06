#ifndef CHATINVITEDFORM_H
#define CHATINVITEDFORM_H

#include <QWidget>

namespace Ui {
class ChatInvitedForm;
}

class ChatInvitedForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatInvitedForm(QWidget *parent = nullptr);
    ~ChatInvitedForm();

private:
    Ui::ChatInvitedForm *ui;
};

#endif // CHATINVITEDFORM_H
