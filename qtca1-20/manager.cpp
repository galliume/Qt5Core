
#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent)
{

}

Manager::~Manager()
{
    quit();
}

void Manager::process()
{
    QtConcurrent::run(Manager::createWorker, this);
}

void Manager::quit()
{
    qInfo() << this << " Quit " << QThread::currentThread();
    emit stop();
}

void Manager::createWorker(Manager *manager)
{
    qInfo() << "Created worker";

    Worker* worker = new Worker();

    connect(manager, &Manager::start, worker, &Worker::start, Qt::QueuedConnection);
    connect(manager, &Manager::stop, worker, &Worker::stop, Qt::QueuedConnection);


    worker->start();
}
