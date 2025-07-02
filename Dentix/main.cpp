#include "mainwindow.h"
#include "firstscreen.h"
#include "patientwindow.h"
#include <QApplication>
#include "chatpopup.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    FirstScreen w;
    chatPopUp c;
    c.show();


    return a.exec();
}
