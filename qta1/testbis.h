#ifndef TESTBIS_H
#define TESTBIS_H

#include <QObject>
#include <QThread>
#include <QDebug>

class testBis : public QThread
{
    Q_OBJECT
public:
    testBis();

public slots:
    void quit();
protected:
    void run();
private:
    bool ok;
};

#endif // TESTBIS_H
