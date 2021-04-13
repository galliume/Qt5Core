#include <QCoreApplication>
#include "client.h"

// /!\ add <QT += network> to project file

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToHost("httpbin.org", 80);

    return a.exec();
}
