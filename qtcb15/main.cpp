#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QVariant>

#include "cat.h"

void test(QObject* obj) {
    qInfo() << obj;
}

void test(QVariant value) {
    qInfo() << value;

    int test = 0;
    bool ok = false;

    test = value.toInt(&ok);

    if (ok) {
        qInfo() << "INT = " << test;
    } else {
        qInfo() << "Not a number";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QObject
    cat kitty;
    kitty.setObjectName("Alberto");
    test(&kitty);

    //QInt xxx bit guaranteed on all platforms
    qint8 value8 = 0;
    qint16 value16 = 0;
    qint32 value32 = 0;
    qint64 value64 = 0;
    qintptr valueptr = 0;

    Q_UNUSED(value8); //hide warning

    //QString support unicode out of the box
    QString name = "Galliume";
    qInfo() << name.mid(1, 3);
    qInfo() << name.insert(0, "P. ");
    qInfo() << name.split(" ");
    qInfo() << name.toLatin1();

    //QDate
    QDate today = QDate::currentDate();
    qInfo() << today;
    qInfo() << today.addDays(1);
    qInfo() << today.addYears(20);
    qInfo() << today.toString(Qt::DateFormat::SystemLocaleDate);
    qInfo() << today.toString(Qt::DateFormat::TextDate);

    //QTime
    QTime now = QTime::currentTime();
    qInfo() << now;
    qInfo() << now.toString(Qt::DateFormat::DefaultLocaleLongDate);
    qInfo() << now.toString(Qt::DateFormat::DefaultLocaleShortDate);

    //QDateTime
    QDateTime current = QDateTime::currentDateTime();
    qInfo() << current;

    QDateTime expire = current.addDays(45);
    qInfo() << expire;

    if (current > expire) {
        qInfo() << "Expired";
    } else {
        qInfo() << "Not expired";
    }

    //QByteArray
    QString greeting = "Hellow World";
    QByteArray buffer(greeting.toLatin1());
    buffer.append("!");

    qInfo() << buffer;
    qInfo() << buffer.rightJustified(20, '.');
    qInfo() << buffer.at(buffer.length() - 1);

    QString modifed(buffer);
    qInfo() << modifed;

    //QVariant
    QVariant value = 1;
    QVariant value2 = "Hellow World";

    test(value);
    test(value2);

    //QStringList
    QString data = "Hello world how are you";
    QStringList lst = data.split(" ");

    qInfo() << lst;
    foreach (QString str, lst) {
        qInfo() << str;
    }

    lst.sort(Qt::CaseInsensitive);
    qInfo() << lst;

    QString myvar = "how";

    if (lst.contains(myvar)) {
        int index = lst.indexOf(myvar);
        qInfo() << index << " " << lst.value(index);
    }

    //QList
    QList<QString> qLst = data.split(" ");
    qLst.insert(3, "aaa");
    foreach (QString str, qLst) {
        qInfo() << str;
    }

    QList<int> ages({10, 20, 30, 40});
    foreach (int age, ages) {
        qInfo() << age;
    }

    //QVector - better performances than QList, use it by default
    QVector<int> vectorAges({10, 20, 30, 40});
    foreach (int age, vectorAges) {
        qInfo() << age;
    }

    return a.exec();
}
