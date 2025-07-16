#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include "client.h"
#include "chatbasicform.h"
class ChatController : public QObject
{
    Q_OBJECT

public:
    //QObject*parent 인자로 받는 생성자 추가
    explicit ChatController(Client* client, QObject *parent = nullptr);
    //chat basic page의 라인에딧 입력창 메세지 컨트롤러에서 처리
    void setUserName(const QString &userName);
    //void sendMessageToServer(QString userName, QString message);
    //내부의 userName을 사용므로 sendMessageToServer 파라미터 변경
    void sendMessageToServer(const QString &message);
public slots:
    //view(chatbasicForm)에서 메세지 전송요청 받는 슬롯
    void receivedMessageData(const QString &message);// 메세지 처리용
private:
//사용자 이름을 저장할 멤버변수 선언
    QString m_userName;
    Client* m_client;//서버에 전송할 때 필요하므로 포인터 추가
    ChatBasicForm *chatBasicForm;
};

#endif // CHATCONTROLLER_H
