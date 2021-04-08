#include <QCoreApplication>
#include <QDebug>
#include "test.h"

template<typename T>
void print(T value) {
    qInfo() << value;
}

template<class T, class F>
T add(T value1, F value2) {
    return value1 + value2;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    print<int>(1);
    print<double>(1.3);
    print<QString>("Hello world");

    qInfo() << add(1, 4.6);
    qInfo() << add(1.23, 4.6);
    qInfo() << add(1.23, true);

    test<int> intCalc;
    qInfo() << intCalc.add(1, 4);

    test<double> doubleCalc;
    qInfo() << doubleCalc.add(1.36, 4.02);

    test<QString> qstringCalc;
    qInfo() << qstringCalc.add("Hello", " World");

    return a.exec();
}
