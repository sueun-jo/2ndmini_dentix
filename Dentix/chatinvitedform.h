#ifndef CHATINVITEDFORM_H
#define CHATINVITEDFORM_H

#include <QWidget>

namespace Ui {
class ChatInvitedForm;
}

class ChatInvitedForm : public QWidget
{
    Q_OBJECT
signals:
    void sendMessageSubmit(const QString &message, const QString &chatRoomId);

public:
    explicit ChatInvitedForm(QWidget *parent = nullptr, const QString &chatRoomId ="초대된채팅");
    ~ChatInvitedForm();

private slots:

    void on_btnSendInvited_clicked();

private:
    Ui::ChatInvitedForm *ui;
    QString m_chatRoomId;
};

#endif // CHATINVITEDFORM_H
