#include <QCoreApplication>
#include <QDebug>
#include <QLinkedList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QLinkedList<int>list;//constant (predictable) time insertions

    for (int i = 0; i < 10; i++) {
        list.append(i);
    }

    list.removeFirst();
    list.removeLast();
    list.removeOne(5);

    if (list.contains(3)) qInfo() << "Contains 3";

    list.clear();

    return a.exec();
}
