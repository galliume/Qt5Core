#include <QCoreApplication>
#include <QDebug>
#include <QSharedPointer>

#include "test.h"
#include "consumer.h"

void doDeleteLater(test* obj) {
    qInfo() << "Deleting " << obj;
    obj->deleteLater();//delete if there is no more references to it
}

QSharedPointer<test>createPointer() {
    test* t = new test();//the bad way, created on the heap
    t->setObjectName("testObject");

    QSharedPointer<test>p(t, doDeleteLater);
    return p;
}

void doStuff(QSharedPointer<consumer> ptr) {
    qInfo() << "In function " << ptr.data()->tester;

    ptr.clear();//clear the references to it but don't delete the pointer
}

QSharedPointer<consumer> makeConsumer() {

   QSharedPointer<consumer>  c(new consumer, &QObject::deleteLater);
   QSharedPointer<test> t = createPointer();

   c.data()->tester.swap(t);
   doStuff(c);

   return c;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QSharedPointer<consumer> consume = makeConsumer();
    qInfo() << "In main" << consume.data()->tester;

    consume.clear();

    return a.exec();
}
