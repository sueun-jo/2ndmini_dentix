#ifndef CHATLOGWORKER_H
#define CHATLOGWORKER_H

#include <QObject>
#include <QVector>
#include <QString>

class Chat;

class ChatLogWorker : public QObject
{
    Q_OBJECT
public slots:
    void saveChats(const QVector<Chat*>& chats, const QString& filepath);
signals:
    void saveDone();
};

#endif // CHATLOGWORKER_H
