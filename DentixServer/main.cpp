#include "server.h"

#include <QApplication>
#include "serverwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server::getInstance()->startServer(54321);

    ServerWindow s;
    s.show();
    return a.exec();
}
