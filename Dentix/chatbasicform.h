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

public:
    explicit ChatBasicForm(QWidget *parent = nullptr);
    ~ChatBasicForm();

signals:
    void sendMessageData(const QString &message);

private slots:
    void on_btnSendChat_clicked();//send 버튼

private:
    Ui::ChatBasicForm *ui;
};

#endif // CHATBASICFORM_H
