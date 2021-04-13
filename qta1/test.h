#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QThread>

class test : public QObject
{
    Q_OBJECT
public:
    test();

public slots:
    void timeout();
    void start();

private:
    QTimer timer;
};

#endif // TEST_H
