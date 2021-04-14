#ifndef CAT_H
#define CAT_H

#include <QObject>
#include <QDebug>
#include <QtTest/QtTest>
#include <QTest>

class Cat : public QObject
{
    Q_OBJECT
public:
    explicit Cat(QObject *parent = nullptr);       

    void setName(QString name);

private:
    QString name;

signals:

public slots:
    void test();

private slots:

    void meow();
    void sleep();
    void speak(QString value);

    void testFail();
    void testName_data();
    void testName();
//    void testCat();

    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();
    void rollover();

};

#endif // CAT_H
