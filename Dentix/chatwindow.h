#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

class ChatBasicForm;
class ChatGroupForm;
class ChatInvitedForm;

namespace Ui {
class ChatBasicForm;
class ChatGroupForm;
class ChatInvitedForm;
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

    void setChatTabs(ChatBasicForm* basic);
private:
    Ui::ChatWindow *ui;
    ChatBasicForm* chatForm;

};

#endif // CHATWINDOW_H



