#include <QCoreApplication>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QThreadPool>

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

    return a.exec();
}
