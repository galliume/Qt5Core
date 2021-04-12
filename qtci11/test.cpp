#include "test.h"

test::test(QObject *parent) : QObject(parent)
{
    number = 0;
    timer.setInterval(1000);

    connect(&timer, &QTimer::timeout, this, &test::timeout);
}

void test::timeout()
{
    number++;

    qInfo() << QTime::currentTime().toString(Qt::DateFormat::SystemLocaleLongDate);

    if (number == 5) {
        timer.stop();
        qInfo() << "complete";
    }
}

void test::dostuff()
{
    timer.start();
}
