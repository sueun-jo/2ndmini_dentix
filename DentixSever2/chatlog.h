#ifndef CHATLOG_H
#define CHATLOG_H

#include <QWidget>

namespace Ui {
class ChatLog;
}

class ChatLog : public QWidget
{
    Q_OBJECT

public:
    explicit ChatLog(QWidget *parent = nullptr);
    ~ChatLog();

private:
    Ui::ChatLog *ui;
};

#endif // CHATLOG_H
