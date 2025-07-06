#include "usermanager.h"
#include "userrepository.h"
#include <QDebug>

UserManager::UserManager() {
    // users.json에서 모든 사용자 불러오기
    users = repository.loadAllUsers("users.json");
}

bool UserManager::login(const QString& name, const QString& pw) {
    for (User& user : users) {
        if (user.getName() == name && user.getPassword() == pw) {
            user.setOnline(true);
            repository.saveAllUsers(users, "users.json");  // 로그인 상태 저장
            qDebug() << "[UserManager] 로그인 성공:" << name;
            return true;
        }
    }
    qDebug() << "[UserManager] 로그인 실패:" << name;
    return false;
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
