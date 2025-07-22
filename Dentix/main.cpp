
#include "appcontroller.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <stdio.h>
#include <stdlib.h>

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", qPrintable(msg));
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", qPrintable(msg));
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", qPrintable(msg));
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", qPrintable(msg));
        abort(); // 꼭 필요: FatalMsg는 예외 없이 종료됨
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageHandler);
    QApplication a(argc, argv);

    AppController Ac;
    Ac.startApplication();


    return a.exec();
}
