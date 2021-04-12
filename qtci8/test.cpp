#include "test.h"

test::test()
{

}

void test::fill()
{
    m_name = "test object";

    for (int i = 0; i < 10; i++) {
        QString num = QString::number(i);
        QString key = "key " + num;
        QString value = "This is item number " + num;
        m_map.insert(key, value);
    }
}

QString test::name()
{
    return m_name;
}

void test::setName(QString value)
{
    m_name = value;
}

QMap<QString, QString> test::map() {
    return m_map;
}
