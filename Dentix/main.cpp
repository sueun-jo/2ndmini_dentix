#include "mainwindow.h"
#include "firstscreen.h"
#include "patientwindow.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client* client = new Client;
    client->connectToServer("127.0.0.1", 54321);

    FirstScreen w;
    w.show();
    return a.exec();
}
