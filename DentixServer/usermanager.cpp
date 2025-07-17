#include "usermanager.h"
#include "userrepository.h"
#include "responsefactory.h"
#include <QDebug>


UserManager::UserManager() {
    // users.json에서 모든 사용자 불러오기
    users = repository.loadAllUsers("users.json");
}

QJsonObject UserManager::login(const QString& name, const QString& pw, QTcpSocket* socket) {

    //전체 회원 목록에서 name/pw인증
    bool found = false;
    for (const User& user : users){
        if (user.getName() == name && user.getPassword() == pw){
            found = true;
            break;
        }
    }

    if (found){
        for (User* user : onlineUsers){
            if (user->getSocket() == socket){
                user->setName(name);
                break;
            }
        }
        QJsonObject data;
        data["name"] = name;
        return ResponseFactory::createResponse("login", "success", data);
    } else {
    return ResponseFactory::createResponse("login", "fail", {{"reason", "user not found"}});

    }
}

QVector<User> UserManager::getAllUsers() const {
    return users; // 그냥 user목록 전체
}

QVector<User*> UserManager::getOnlineUsers() const{
    return onlineUsers; //온라인인 애들
}
void UserManager::connectUser(User* user){
    onlineUsers.append(user);
}

void UserManager::disconnectUser(QTcpSocket* socket){
    auto it = std::remove_if(onlineUsers.begin(), onlineUsers.end(),
                     [socket](User* u){ return u->getSocket() == socket; });
    if (it != onlineUsers.end()) {
    delete *it;
    onlineUsers.erase(it, onlineUsers.end());
    }
}

User* UserManager::findUserBySocket(const QTcpSocket* socket) const{
    qDebug() << "find user by socket ..." << socket;
    for (User* user : onlineUsers){
        if (user->getSocket() == socket){
            return user;
        }
    }
    return nullptr;
}
