
#include "appcontroller.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /* sueun code in main.cpp 0705 */

    // FirstScreen* firstScreen = new FirstScreen;


    // firstScreen->show();
    AppController Ac;
    Ac.startApplication();



    /*****************************/


    return a.exec();
}
