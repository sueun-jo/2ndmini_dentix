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

    /* from howon */
    // MainWindow w;
    // FirstScreen w;
    // chatPage c;
    // patient p;
    // p.show();

    /* sueun code */
    Client* client = new Client;

    FirstScreen w(client);
    w.show();
    return a.exec();
}
