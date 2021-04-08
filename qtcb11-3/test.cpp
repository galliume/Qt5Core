#include "test.h"

test::test()
{

}

QString test::message()
{
    return m_message;
}

void test::setMessage(QString value)
{
    m_message = value;
    emit messageChanged(m_message);
}
