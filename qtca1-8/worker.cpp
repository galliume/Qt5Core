#include "worker.h"

Worker::Worker(QObject *parent, QStringList *data, QSemaphore *sema, int position) :
    data(data), sema(sema), position(position)
{

}

void Worker::run()
{
    if (!data || !sema) {
        qInfo() << "Missing pointers";
        return;
    }

    QString t;
    t.sprintf("%08p", QThread::currentThread());
    sema->acquire(1);
    data->replace(position, QString::number(position) + " - " + t);
    sema->release();

    qInfo() << t << " Finished " << position;
}
