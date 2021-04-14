#include <QCoreApplication>
#include <QTest>

#include "cat.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Cat cat;
    QTest::qExec(&cat);

    return a.exec();
}
