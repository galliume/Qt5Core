
#include "consumer.h"

Consumer::Consumer(QObject *parent) : QObject(parent)
{
    qInfo() << "Created " << QThread::currentThread();

    thread.setObjectName("TimerThread");

    //Qt::AutoConnection (see doc)
    //Qt::DirectConnection (see doc)
    //Qt::QueuedConneciton <- with thread explicitly use this one

    connect(&timer, &Timer::timeout, this, &Consumer::timeout, Qt::QueuedConnection);
    connect(&thread, &QThread::started, &timer, &Timer::started, Qt::QueuedConnection);
    connect(&thread, &QThread::finished, this, &Consumer::finished, Qt::QueuedConnection);
}

void Consumer::timeout()
{
    qInfo() << "Consumer timeout on " << QThread::currentThread();
    thread.quit();
}

void Consumer::start()
{
    qInfo() << "Consumer start " << QThread::currentThread();
    timer.setInterval(500);
    timer.moveToThread(&thread);
    thread.start();
}

void Consumer::finished()
{
    qInfo() << "Consumer finished " << QThread::currentThread();
}
