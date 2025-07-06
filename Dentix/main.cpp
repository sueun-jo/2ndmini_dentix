#include "mainwindow.h"
#include "firstscreen.h"
#include "client.h"
#include <QApplication>
#include "chatpopup.h"
#include "chatPage.h"
#include "patient.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /* sueun code in main.cpp 0705 */
    Client* client = new Client;
    FirstScreen* firstScreen = new FirstScreen;

    QObject::connect(firstScreen, &FirstScreen::connectToServer,
                     client, &Client::connectToServer);

    QObject::connect(firstScreen, &FirstScreen::requestLogin,
                     client, &Client::requestLogin);

    firstScreen->show();

    return a.exec();
}
