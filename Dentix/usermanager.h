// #ifndef USERMANAGER_H
// #define USERMANAGER_H

// #include <QObject>
// #include <QStringList>
// #include <QByteArray>
// #include <QJsonDocument>
// #include <QJsonObject>
// #include <QJsonArray>

// class UserManager : public QObject
// {
//     Q_OBJECT
// public:
//     explicit UserManager(QObject *parent = nullptr);

// signals:
//     void userListUpdated(const QStringList &userList);  // ChatBasicForm으로 전달

// public slots:
//     void handleRawJson(const QByteArray &jsonData);     // Client로부터 전달받는 JSON

// private:
//     QStringList m_userList; // 현재 접속자 목록 저장
// };

// #endif // USERMANAGER_H
