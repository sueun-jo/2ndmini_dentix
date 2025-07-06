#include "usermanager.h"
#include "userrepository.h"
#include "responsefactory.h"
#include <QDebug>


UserManager::UserManager() {
    // users.json에서 모든 사용자 불러오기
    users = repository.loadAllUsers("users.json");
}

QJsonObject UserManager::login(const QString& name, const QString& pw) {
    for (User& user : users) {
        if (user.getName() == name) {
            if (user.getPassword() == pw) {
                user.setOnline(true);
                repository.saveAllUsers(users, "users.json");

                QJsonObject data;
                data["name"] = name;

                return ResponseFactory::createResponse("login", "success", data);
            } else {
                return ResponseFactory::createResponse("login", "fail", {{"reason", "wrong password"}});
            }
        }
    }
    return ResponseFactory::createResponse("login", "fail", {{"reason", "user not found"}});
}

void UserManager::setOnlineStatus(const QString& name, bool online) {
    for (User& user : users) {
        if (user.getName() == name) {
            user.setOnline(online);
            repository.saveAllUsers(users, "users.json");
            qDebug() << "[UserManager] 온라인 상태 변경:" << name << "->" << (online ? "온라인" : "오프라인");
            return;
        }
    }
    qDebug() << "[UserManager] 온라인 상태 변경 실패: 유저 없음:" << name;
}

QVector<User> UserManager::getAllUsers() const {
    return users;
}
