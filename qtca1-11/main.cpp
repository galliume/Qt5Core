#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "consumer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("MainThread");
    qInfo() << "Application started on " << QThread::currentThread();

    Consumer consumer;
    consumer.start();

    return a.exec();
}
