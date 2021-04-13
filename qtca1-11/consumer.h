#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "timer.h"

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);

public slots:
    void timeout();
    void start();
    void finished();
private:
    QThread thread;
    Timer timer;
};

#endif // CONSUMER_H
