#include <QCoreApplication>
#include <QDebug>

#include "worker.h"

 // /!\ add <QT += network> to the project file

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker;
    worker.start();

    return a.exec();
}
