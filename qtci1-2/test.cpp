#include "test.h"

test::test(QObject *parent)
{

}

void test::useWidget()
{
    if (!widget.data()) {
        qInfo() << "No pointer.";
        return;
    }

    qInfo() << "Widget = " << widget.data();

    widget.data()->setObjectName("used Widget");
}
