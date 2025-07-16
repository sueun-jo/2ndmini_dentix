#ifndef CHATGROUPFORM_H
#define CHATGROUPFORM_H

#include <QWidget>

namespace Ui {
class ChatGroupForm;
}

class ChatGroupForm : public QWidget
{
    Q_OBJECT
signals:
    void sendMessageSubmit(const QString &message, const QString &chatRoomId);

public:
    explicit ChatGroupForm(QWidget *parent = nullptr, const QString &chatRoomId = "그룹채팅");
    ~ChatGroupForm();

private slots:
    void on_btnSendGroup_clicked();

private:
    Ui::ChatGroupForm *ui;
    QString m_chatRoomId;
};

#endif // CHATGROUPFORM_H
