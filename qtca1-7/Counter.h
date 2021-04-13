#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QDebug>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = nullptr);

    void increment();
    void decrement();
    int count();

private:
    int value = 0;
signals:

};

#endif // COUNTER_H
