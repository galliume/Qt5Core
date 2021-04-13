#include <QCoreApplication>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QThreadPool>
#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QFutureIterator>
#include <QFutureSynchronizer>

#include "test.h"

// /!\ for QtConcurrent we need to add <QT += concurrent> in project file

int doMap(int value) {
    qInfo() << "Do stuff " << value;
    int  num = value * 10;
    return num;
}

void loop() {
    for (int i = 0; i < 10; i++) {
        qInfo() << "Loop " << i << " on " << QThread::currentThread();
    }
}

void test() {
    qInfo() << "Test " << QThread::currentThread();
    loop();
}

void testIssue(QString name, int max) {
    for (int i = 0; i < max; i++) {
        qInfo() << name << " " << i << " " << QThread::currentThread();
    }
}

int multiply(const int &value) {
    qInfo() << "Called " << value ;
    int num = value * 10;
    return num;
}

void doStuff(int value) {
    for (int i = 0; i < 10; i++) {
        QThread::currentThread()->msleep(100);
        qInfo() << "Thread " << value << " " << i;
    }
}

void runthread() {
    QFutureSynchronizer<void>sync;
    for (int i = 0; i < 10; i++) {
        QFuture<void> f = QtConcurrent::run(&doStuff, i);
        sync.addFuture(f);
    }

    //waitForFinished is called in the QFutureSynchronizer deconstructor
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<int> values;
    for (int i = 0; i < 9; i++) {
        values <<  i;
    }

    qInfo() << "Starting blocked";
    QList<int> updated = QtConcurrent::blockingMapped(values, &doMap);

    qInfo() << updated;
    qInfo() << "Finished ";

    QThread::currentThread()->setObjectName("Main");

    QThreadPool pool;
    QFuture<void> future = QtConcurrent::run(&pool, test);
    qInfo() << "Main " << QThread::currentThread();
    loop();

    // -> error: array used as initializer
    //QFuture<void> futureIssue = QtConcurrent::run(testIssue, "name", 5);

    //solution : create a variable QString -_O_-
    QString name = "name";
    QFuture<void> futureIssue = QtConcurrent::run(testIssue, name, 5);

    QList<int>list;
    for (int i = 0; i < 100; i++) {
        list.append(i);
    }

    QFutureWatcher<int> watcher;
    //QFuture<void> futureW = QtConcurrent::map(list, &multiply);
    QFuture<int> futureW = QtConcurrent::mapped(list, &multiply);
    watcher.setFuture(futureW);

    watcher.waitForFinished();

    qInfo() << "done ";
    //qInfo() << list;
    qInfo() << futureW.results();


    Test test;
    test.process();


    QList<int> listBis;
    for (int i = 0; i < 100; i++) {
        listBis.append(i);
    }

    QFutureWatcher<int> watcherBis;
    QFuture<int> futureBis = QtConcurrent::mapped(list, &multiply);
    watcherBis.setFuture(futureBis);

    watcherBis.waitForFinished();

    QFutureIterator<int> iter(futureBis);

    while (iter.hasNext()) {
        qInfo() << iter.next();
    }

    qInfo() << "----------";

    for (int i = 0; i < futureBis.results().length(); i++) {
        qInfo() << futureBis.resultAt(i);
    }

    qInfo() << "----------";

    foreach (int i, futureBis.results()) {
        qInfo() << i;
    }

    qInfo() << "----------";

    QList<int>valuesBis = futureBis.results();

    for (auto i = values.begin(); i < values.end(); i++) {
        qInfo() << *i;
    }

    qInfo() << "Done";


    qInfo() << "QFutureSynchronizer STARTED";
    runthread();
    qInfo() << "QFutureSynchronizer Done";

    return a.exec();
}
