#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

#include "test.h"
#include "watcher.h"

void testTimer() {
    qInfo() << "Thank you for waiting";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "please wait";
    QTimer::singleShot(3000, &testTimer);

    test t;
    t.dostuff();

    watcher w;


    return a.exec();
}
