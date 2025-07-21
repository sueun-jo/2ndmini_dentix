#ifndef CHATLOGFORM_H
#define CHATLOGFORM_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QMap>
#include <QTimer>
#include "ui_chatlogform.h"
#include "chatmanager.h"
#include "chat.h"

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

    void on_saveButton_clicked();

    void on_test_clicked();

public:
    void appendChat(Chat* chat);

private:
    Ui::ChatLogForm *ui;
    QMap<QString, QPlainTextEdit*> logMap;
    QVBoxLayout* logLayout; //logTextEdit들 쌓는 레이아웃
    QTimer* autoSaveTimer;

signals:
    void requestSaveChats(const QVector<Chat*>&, const QString&);
};

#endif // CHATLOGFORM_H
