#ifndef CHATMANAGER_H
#define CHATMANAGER_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
class ChatManager: public QObject
{
    Q_OBJECT
signals:
    void chatJsonReadyToSend(const QByteArray &jsonData);
    void requestUserListToServer(const QByteArray &sendData);
public:
    explicit ChatManager(QObject *parent = nullptr);
    void setUserName(const QString &userName);
    void sendMessageToServer(const QString &message, const QString &chatRoomId);
public slots:
    //view(chatbasicForm)에서 메세지 전송요청 받는 슬롯
    void handleChatMessage(const QString &message, const QString &chatRoomId);// 메세지 처리용
    void requestUserList();
private:
//사용자 이름을 저장할 멤버변수 선언
    QString m_userName;
};

#endif // CHATMANAGER_H
