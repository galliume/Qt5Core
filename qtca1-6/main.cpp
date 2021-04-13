#include <QCoreApplication>
#include <QThread>
#include <QThreadPool>
#include <QDebug>

#include "counter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("Main");
    QThreadPool* pool = QThreadPool::globalInstance();

    qInfo() << "max thread count " << pool->maxThreadCount();

    for (int i = 0; i < 100; i++) {
        counter* c = new counter;
        c->setAutoDelete(true);

        pool->start(c);
    }

    return a.exec();
}
