#ifndef CHATLOGFORM_H
#define CHATLOGFORM_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

namespace Ui {
class ChatLogForm;
}

class ChatLogForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatLogForm(QWidget *parent = nullptr);
    ~ChatLogForm();

private slots:
    void on_logList_itemClicked(QListWidgetItem *item);

private:
    Ui::ChatLogForm *ui;
};

#endif // CHATLOGFORM_H
