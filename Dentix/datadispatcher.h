#ifndef DATADISPATCHER_H
#define DATADISPATCHER_H

#include <QObject>
#include <QByteArray>

class DataDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit DataDispatcher(QObject *parent = nullptr);

signals:
    void loginReceivedJson(const QByteArray &data);        // LoginManager로 emit
    void dataSendToBasic(const QByteArray &data);
    void patientInfo(const QByteArray &data);
    void updateOnlineUserlist(const QByteArray &data);
// void dataSendToGroup(const QByteArray &data);  // 채팅 메시지
// void dataSendToInvtied(const QByteArray &data);
// void userEventReceivedJson(const QByteArray &data); //나중에 구현 예정

public slots:
    void SignalHandler(const QByteArray &data);
    void chatSignalHandler(const QByteArray &data);     // ChatManager로
private:
};

#endif // DATADISPATCHER_H
