#include "mainwindow.h"
#include "firstscreen.h"
#include "patientwindow.h"
#include "client.h"

#include <QApplication>
#include "chatpopup.h"
#include "chatPage.h"
#include "patient.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    // MainWindow w;
    FirstScreen w;
    chatPage c;
    patient p;
    p.show();


    Client* client = new Client;
    client->connectToServer("127.0.0.1", 54321); //서버 연결

    FirstScreen w(client);
    w.show();
    return a.exec();
}
