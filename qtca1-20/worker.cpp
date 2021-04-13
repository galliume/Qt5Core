
#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    qInfo() << this << " Constructed " << QThread::currentThread();

    connect(&timer, &QTimer::timeout, this, &Worker::timeout);

    timer.setInterval(1000);
}

Worker::~Worker()
{
    qInfo() << this << " Deconstructed " << QThread::currentThread();
}

void Worker::start()
{
    qInfo() << this << " Started " << QThread::currentThread();

    timer.start();

    loop.exec();

    qInfo() << this << " Loop finished " << QThread::currentThread();

    //this->deleteLater();//could keep this for a while
    delete this;
}

void Worker::stop()
{
    timer.stop();
    loop.quit();

    qInfo() << this << " Stopped " << QThread::currentThread();

}

void Worker::timeout()
{
    qInfo() << this << " Timeout " << QThread::currentThread();

}
