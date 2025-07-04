#include "mainwindow.h"
#include "firstscreen.h"
#include "client.h"
#include <QApplication>
#include "chatpopup.h"
#include "chatPage.h"
#include "patient.h"
int main(int argc, char *argv[])
{
    //merge용 주석
    QApplication a(argc, argv);


    /* from howon */
    // MainWindow w;
    // FirstScreen w;
    // chatPage c;
    // patient p;
    // p.show();


    /* sueun code */
    Client* client = new Client;


    return a.exec();
}
