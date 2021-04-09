#include "consumer.h"

consumer::consumer(QObject *parent)
{
    qInfo() << this << "Constructed" << this;

}

consumer::~consumer()
{
    qInfo() << this << "Deconstructed" << this;
}
