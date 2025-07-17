#ifndef SERVERINFOFORM_H
#define SERVERINFOFORM_H

#include <QWidget>

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
private:
    Ui::ServerInfoForm *ui;
    static ServerInfoForm* m_instance;

public slots:
    void appendLog(const QString& msg);

private slots:
    void on_startServer_clicked();

signals:
    void logMessage(const QString &msg);
};

#endif // SERVERINFOFORM_H
