#include "consumer.h"

Consumer::Consumer(QObject *parent) : QObject(parent)
{

}

void Consumer::setData(QList<int> *data)
{
    this->data = data;
}

void Consumer::setMutex(QMutex *mutex)
{
    this->mutex = mutex;
}

void Consumer::setCondition(QWaitCondition *condition)
{
    this->condition = condition;
}

void Consumer::start()
{
    qInfo() << "Starting consummer " << this->thread();

    do {
        qInfo() << "Consuming " << this->thread();


        mutex->lock();

        //do stuff with data
        data->clear();

        condition->wait(mutex);//"pause"

        mutex->unlock();

    }  while (true);

}
