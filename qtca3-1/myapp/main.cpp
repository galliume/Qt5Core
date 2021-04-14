#include <QCoreApplication>

#include "../myLib/myLib_global.h"
#include "../myLib/mylib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyLib mylib;
    mylib.test();

    return a.exec();
}
