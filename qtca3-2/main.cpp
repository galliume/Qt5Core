#include <QCoreApplication>

#include "myLib_global.h"
#include "mylib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyLib lib;
    lib.test();

    return a.exec();
}
