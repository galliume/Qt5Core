#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

class counter : public QObject
{
    Q_OBJECT
public:
    counter();

signals:
public slots:
    void start();
};

#endif // COUNTER_H
