#include "mylib.h"

Mylib::Mylib(QObject *parent)
{

}

void Mylib::test(QString name)
{
    qInfo() << "test from plugin " << name;
}
