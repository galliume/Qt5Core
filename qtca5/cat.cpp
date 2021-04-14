#include "cat.h"

Cat::Cat(QObject *parent) : QObject(parent)
{
    name = "kitty";
}

void Cat::setName(QString name)
{
    this->name = name;
}

void Cat::test()
{
    qInfo() << "test";
}

void Cat::initTestCase()
{
    qInfo() << "initTestCase";

}

void Cat::init()
{
    qInfo() << "init";
}

void Cat::cleanup()
{
    qInfo() << "cleanup";

}

void Cat::cleanupTestCase()
{
    qInfo() << "cleanupTestCase";
}

void Cat::rollover()
{
    qInfo() << "rollover";
}

void Cat::meow()
{
    qInfo() << "meow";
}

void Cat::sleep()
{
    qInfo() << "sleep";
}

void Cat::speak(QString value)
{
    qInfo() << "speak " << value;
}

void Cat::testFail()
{
    QFAIL("FAILED");
}

void Cat::testName_data()
{
    qInfo() << "generating data";
    QTest::addColumn<QString>("name");

    QTest::addRow("Invalid") << "Name";
    QTest::addRow("Invalid") << "fido";
    QTest::addRow("Invalid") << "";
    QTest::addRow("Invalid") << "kitty";

    qInfo() << "data generated";
}

void Cat::testName()
{
    QFETCH(QString, name);

    qInfo() << "Test name" << name;

    if (name.isEmpty()) QFAIL("Name is not set");
    if (name == "Name") QWARN("default name");
    if (name == "fido") QFAIL("that's a dog name");

    QCOMPARE(this->name, name);
}

//void Cat::testCat()
//{
//    QString value = "Name";
//    QVERIFY(name != "");

//    if (name == "Name") QWARN("default name");
//    if (name == "fido") QFAIL("that's a dog name");

//    QCOMPARE(name, value);
//}
