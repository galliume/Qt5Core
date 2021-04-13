#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "counter.h"

class manager : public QObject
{
    Q_OBJECT
public:
    manager();
    void start();

public slots:
    void started();
    void finished();
private:
    QList<QThread*> threads;
};

#endif // MANAGER_H
