#include "station.h"

station::station(QObject *parent, int channel, QString name) : QObject(parent)
{
    this->channel = channel;
    this->name = name;
}

void station::broacast(QString message)
{
    emit send(channel, name, message);
}
