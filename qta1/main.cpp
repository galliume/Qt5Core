#include <QCoreApplication>

#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QSharedPointer>

#include "testbis.h"
#include "test.h"
#include "manager.h"

static QSharedPointer<QThread>sptr;
void timeout() {
    if (!sptr.isNull()) {
        qInfo() << "Time out - stopping other thread from " << QThread::currentThread();
        sptr.data()->quit();
    }
}

static QSharedPointer<testBis>testptr;
void timeoutBis() {
    if (!testptr.isNull()) {
        qInfo() << "Time out - stopping other thread from " << QThread::currentThread();
        testptr.data()->quit();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "App thread" << a.thread();
    qInfo() << "Current thread" << QThread::currentThread();

    Q_ASSERT(a.thread() == QThread::currentThread());

    qInfo() << "Running " << QThread::currentThread()->isRunning();
    qInfo() << "Loop level " << QThread::currentThread()->loopLevel();
    qInfo() << "Stack size " << QThread::currentThread()->stackSize();
    qInfo() << "Finished " << QThread::currentThread()->isFinished();
    qInfo() << "Before " << QDateTime::currentDateTime().toString();
    QThread::sleep(1);
    qInfo() << "After " << QDateTime::currentDateTime().toString();


    qInfo() << "App thread" << a.thread();
    qInfo() << "Current thread" << QThread::currentThread();

    test t;//can't move to a thread with a parent, so no parent with thread
    qInfo() << "Timer thread" << t.thread();

    QThread thread;
    sptr.reset(&thread);
    t.moveToThread(&thread);
    qInfo() << "Timer thread" << t.thread();

    t.start();

    qInfo() << "Thread state " << thread.isRunning();
    thread.start();

    QTimer timer;
    timer.singleShot(5000, &timeout);

    testBis threadBis;
    testptr.reset(&threadBis);
    threadBis.start();

    QTimer timerbis;
    timerbis.singleShot(5000, &timeoutBis);

    QThread::currentThread()->setObjectName("Main");
    manager m;
    m.start();

    return a.exec();
}
