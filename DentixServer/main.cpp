#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server::getInstance()->startServer(54321);

    return a.exec();
}
