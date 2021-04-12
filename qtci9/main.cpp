#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QtAlgorithms>
#include <QVector>
#include <QRandomGenerator>
#include "test.h"

void random(QVector<int> *list, int max) {
    list->reserve(max);
    for (int i = 0; i < max; i++) {
        int value = QRandomGenerator::global()->bounded(1000);
        list->append(value);
    }
}

//custom macro
#define add(a, b) a + b

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<test*> list;

    for (int i = 0; i < 10; i++) {
        test *t = new test();
        t->setObjectName(QString::number(i));
        list.append(t);
    }

    qInfo() << list.at(0);

    qDeleteAll(list);//delete pointers

    //crash
    //qInfo() << list.at(0);

    //objects are invalid pointers
    list.clear();

    QVector<int> listFill;
    listFill << 1 << 2 << 3 << 4;

    //qFill(listFill, 0);//deprecated
    listFill.fill(0);

    QVector<int> listSort;
    random(&listSort, 10);

    qInfo() << "unsorted " << listSort;
    //qSort(list);//depracted
    std::sort(listSort.begin(), listSort.end());
    qInfo() << "sorted " << listSort;

    QVector<int> list1;
    random(&list1, 10);

    QVector<int> list2;
    random(&list2, 10);

    qInfo() << list1;
    qInfo() << list2;
    //qInfo() << "Equals " << qEqual(list1.begin(), list1.end(), list2.begin());//deprecated
    //qCopy(list1.begin(), list1.end(), list2.begin());//deprecated
    //qInfo() << "Equals " << qEqual(list1.begin(), list1.end(), list2.begin());//deprecated

    qInfo() << "Equals " << std::equal(list1.begin(), list1.end(), list2.begin());
    std::copy(list1.begin(), list1.end(), list2.begin());
    qInfo() << "Equals " << std::equal(list1.begin(), list1.end(), list2.begin());

    qInfo() << add(1, 2);

    qInfo() << add("Test", 13);
    qInfo() << add(true, true);
    qInfo() << add(true, false);
    qInfo() << add(false, false);
    qInfo() << add("Test", '\n');
    qInfo() << add("Test", '/n');

    return a.exec();
}
