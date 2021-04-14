#ifndef ITEST_H
#define ITEST_H

#include <QObject>

class iTest
{
public:
    virtual void test() = 0;
};

#endif // ITEST_H

Q_DECLARE_INTERFACE(iTest, "iTest")
