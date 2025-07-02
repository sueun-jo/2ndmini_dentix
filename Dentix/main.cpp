#include "mainwindow.h"
#include "firstscreen.h"
#include "patientwindow.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client* client = new Client;
    client->connectToServer("127.0.0.1", 54321); //서버 연결

    FirstScreen w(client);
    w.show();
    return a.exec();
}
