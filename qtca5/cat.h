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
signals:

public slots:
    void test();

private slots:
    void meow();
    void sleep();
    void speak(QString value);
};

#endif // CAT_H
