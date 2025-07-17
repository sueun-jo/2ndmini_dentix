// #include "usermanager.h"
// #include <QDebug>

// UserManager::UserManager(QObject *parent) : QObject(parent)
// {
// }

// void UserManager::handleRawJson(const QByteArray &jsonData)
// {
//     QJsonParseError err;
//     QJsonDocument doc = QJsonDocument::fromJson(jsonData, &err);

//     if (err.error != QJsonParseError::NoError) {
//         qWarning() << "[UserManager] JSON Parse Error:" << err.errorString();
//         return;
//     }

//     if (!doc.isObject()) {
//         qWarning() << "[UserManager] Invalid JSON structure";
//         return;
//     }

//     QJsonObject obj = doc.object();
//     QString type = obj["type"].toString();

//     if (type == "userJoin") {
//         QString newUser = obj["data"].toObject()["name"].toString();
//         if (!m_userList.contains(newUser)) {
//             m_userList.append(newUser);
//             qDebug() << "[UserManager] userJoin:" << newUser;
//             emit userListUpdated(m_userList);
//         }
//     }
//     else if (type == "userLeave") {
//         QString leaveUser = obj["data"].toObject()["name"].toString();
//         if (m_userList.removeOne(leaveUser)) {
//             qDebug() << "[UserManager] userLeave:" << leaveUser;
//             emit userListUpdated(m_userList);
//         }
//     }
//     else if (type == "userList") {
//         QJsonArray users = obj["data"].toObject()["users"].toArray();
//         m_userList.clear();
//         for (const QJsonValue &val : users) {
//             m_userList.append(val.toString());
//         }
//         qDebug() << "[UserManager] Initial user list received:" << m_userList;
//         emit userListUpdated(m_userList);
//     }
//     // 다른 메시지 타입은 무시
// }
