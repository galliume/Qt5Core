#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTime>

class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr);

public slots:
    void timeout();
    void dostuff();

private:
    QTimer timer;
    int number;
};

#endif // TEST_H
