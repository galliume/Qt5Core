#include <QCoreApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test* p = new test(&a);
    //test* p = new test(nullptr); //should have a parent

    p->setObjectName("parent");

    for (int i = 0; i < 5; i++) {
        p->makeChild(QString::number(i));
    }

    //useless with the parent - child  relationship whit QCoreApplication a.
    //a is deleted and by cascade will delete everyting related to it
    //delete p;



    return a.exec();
}
