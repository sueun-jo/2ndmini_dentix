#include "mainwindow.h"
#include "firstscreen.h"
#include "patientwindow.h"
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


    return a.exec();
}
