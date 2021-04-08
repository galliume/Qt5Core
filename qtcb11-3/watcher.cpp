#include "watcher.h"

watcher::watcher()
{

}

void watcher::messageChanged(QString message)
{
    qInfo() << message;
}
