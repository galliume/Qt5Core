#include <QCoreApplication>
#include "source.h"
#include "destination.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    source objSource;
    destination objDestination;

    //connecta signal to a slot
    QObject::connect(&objSource, &source::mySignal, &objDestination, &destination::onMessage);
    //or -> objSource.connect(...);

    objSource.test();

    return a.exec();
}
