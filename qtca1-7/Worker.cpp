#include "Worker.h"

Worker::Worker(QObject *parent, Counter* counter, QMutex* mutex) : counter(counter), mutex(mutex)
{

}

void Worker::run()
{
    if (!counter) return;

    qInfo() << this << " starting";

    for (int i = 0; i < 100; i++) {

        QMutexLocker locker(mutex);

        counter->increment();
        qInfo() << this << " count " << counter->count();
        counter->decrement();
    }

    qInfo() << this << " finished";
}
