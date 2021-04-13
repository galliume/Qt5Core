#include "counter.h"

counter::counter()
{

}

void counter::run()
{
    qInfo() << "Starting " << QThread::currentThread();

    for (int i = 0; i < 20; i++) {
           qInfo() << QThread::currentThread()->objectName() << " " << i;

           auto value = static_cast<unsigned long>(QRandomGenerator::global()->bounded(500));
           QThread::currentThread()->msleep(value);
       }

    qInfo() << "Finished " << QThread::currentThread();
}
