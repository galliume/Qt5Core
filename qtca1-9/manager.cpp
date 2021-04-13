#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent)
{
    //Qt::QueuedConnection when used with threads
    connect(&producerThread, &QThread::started, &producer, &Producer::start, Qt::QueuedConnection);
    connect(&producer, &Producer::ready, this, &Manager::ready, Qt::QueuedConnection);
    connect(&consumerThread, &QThread::started, &consumer, &Consumer::start, Qt::QueuedConnection);

    producerThread.setObjectName("ProducerThread");
    consumerThread.setObjectName("ConsumerThread");
    this->thread()->setObjectName("MainThread");

    producer.moveToThread(&producerThread);
    consumer.moveToThread(&consumerThread);
}

void Manager::start()
{
    producer.setMutex(&mutex);
    producer.setData(&data);

    consumer.setMutex(&mutex);
    consumer.setData(&data);
    consumer.setCondition(&condition);

    producerThread.start();
    consumerThread.start();
}

void Manager::ready()
{
    qInfo() << "Data ready " << this->thread();

    condition.wakeAll();
}
