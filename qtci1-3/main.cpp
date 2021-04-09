#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>

#include "test.h"

void mytest(QScopedPointer<test>pointer) {
    qInfo() << pointer.data();
}

void useit(test* obj) {
    if (!obj) return;

    qInfo() << "Using " << obj;
}

void doStuff() {
    //test* t = new test();//dangling pointer
    QScopedPointer<test>pointer(new test());//will be automatically deleted when out of this scope

    useit(pointer.data());
    //mytest(pointer);//pointer will be out of the scope except if passed by ref &
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    for (int i = 0; i <100; i++) {
        doStuff();
    }

    return a.exec();
}
