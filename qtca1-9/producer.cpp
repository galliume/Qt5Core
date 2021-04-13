#include "producer.h"

Producer::Producer(QObject *parent) : QObject(parent)
{

}

void Producer::setData(QList<int> *data)
{
    this->data = data;
}

void Producer::setMutex(QMutex *mutex)
{
    this->mutex = mutex;
}

void Producer::start()
{
    do {
        int value = QRandomGenerator::global()->bounded(1000);

        mutex->lock();

        data->append(value);

        if (data->length() >= 100) emit ready();

        mutex->unlock();

    } while(true);
}
