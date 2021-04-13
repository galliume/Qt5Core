#include "testbis.h"

testBis::testBis()
{

}

void testBis::quit()
{
    ok = false;
    QThread::quit();
}

void testBis::run()
{
    ok = true;

    for (int i = 0; i < 1000; i++) {
        qInfo() << i;
        this->sleep(1);

        //unpredictable, control can come from anywhere
        //for safe thread use moveToThread instead.
        if (!ok) break;
    }

    qInfo() << "finished";
}
