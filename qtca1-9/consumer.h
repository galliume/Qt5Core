#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QWaitCondition>

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);

    void setData(QList<int>* data);
    void setMutex(QMutex* mutex);
    void setCondition(QWaitCondition* condition);

public slots:
    void start();

private:
    QList<int>*data;
    QMutex* mutex;
    QWaitCondition* condition;
};

#endif // CONSUMER_H
