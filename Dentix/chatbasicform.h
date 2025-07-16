#ifndef CHATBASICFORM_H
#define CHATBASICFORM_H

#include <QWidget>
#include <QString>


namespace Ui {
class ChatBasicForm;
}

class ChatBasicForm : public QWidget
{
    Q_OBJECT

signals:
    void sendMessageSubmit(const QString &message, const QString &chatRoomId);

public:
    explicit ChatBasicForm(QWidget *parent = nullptr, const QString &chatRoomId = "전체채팅");
    ~ChatBasicForm();


private slots:
    void on_btnSendChat_clicked();//send 버튼

private:
    Ui::ChatBasicForm *ui;
    QString m_chatRoomId;
};

#endif // CHATBASICFORM_H
