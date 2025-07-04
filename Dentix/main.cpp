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

    MainWindow mw;

    Client cl;
    mw.show();



    return a.exec();
}
