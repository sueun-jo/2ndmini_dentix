#ifndef CHATBASICFORM_H
#define CHATBASICFORM_H

#include <QWidget>
#include <QString>

#include "chatcontroller.h"

namespace Ui {
class ChatController;
class ChatBasicForm;
}

class ChatBasicForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBasicForm(ChatController *chatController, QWidget *parent = nullptr);
    ~ChatBasicForm();

signals:
    void requestMessage(const QString message);

private slots:
    void on_btnSendChat_clicked();//send 버튼

private:
    Ui::ChatBasicForm *ui;
    ChatController *m_chatController;
};

#endif // CHATBASICFORM_H
