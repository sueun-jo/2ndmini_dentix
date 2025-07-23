#ifndef SERVERINFOFORM_H
#define SERVERINFOFORM_H

#include <QWidget>
#include "chatlogworker.h"

namespace Ui {
class ServerInfoForm;
}

class ServerInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit ServerInfoForm(QWidget *parent = nullptr);
    ~ServerInfoForm();
    static void serverLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static ServerInfoForm* instance();
    void shutdownServer();

private:
    Ui::ServerInfoForm *ui;
    static ServerInfoForm* m_instance;
    ChatLogWorker* logWorker = nullptr;
    QThread* logThread = nullptr;
    QTimer* autoSaveTimer = nullptr;

public slots:
    void appendLog(const QString& msg);

private slots:
    void on_startServer_clicked();
    void on_stopServer_clicked();

signals:
    void logMessage(const QString &msg);
    void requestSaveChats(const QVector<Chat*>& chats, const QString& filepath);
};

#endif // SERVERINFOFORM_H
