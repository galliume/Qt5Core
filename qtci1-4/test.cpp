#include "test.h"

test::test(QObject* parent) : QObject(parent)
{
    qInfo() << this << "Constructed";
}

test::~test()
{
    qInfo() << this << "Deconstructed";

}
