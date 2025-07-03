#ifndef CHATLOG_H
#define CHATLOG_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

namespace Ui {
class ChatLog;
}

class ChatLog : public QWidget
{
    Q_OBJECT

public:
    explicit ChatLog(QWidget *parent = nullptr);
    ~ChatLog();

private slots:
    void on_logList_itemClicked(QListWidgetItem *item);

private:
    Ui::ChatLog *ui;
};

#endif // CHATLOG_H
