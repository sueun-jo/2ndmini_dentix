#include "mainwindow.h"
#include "firstscreen.h"
#include "patientwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    FirstScreen w;
    w.show();
    return a.exec();
}
