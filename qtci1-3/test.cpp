#include "test.h"

test::test(QObject *parent)
{
    qInfo() << "Constructed";
}

test::~test()
{
    qInfo() << "Deconstructed";
}
