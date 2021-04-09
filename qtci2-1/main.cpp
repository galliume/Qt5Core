#include <QCoreApplication>
#include <QVector>
#include <QList>
#include <QDebug>

template<class T>
void fill(T &container) {
    for (int i = 0; i < 5; i++) {
        container.append(i);
    }
}

template<class T>
void display(T &container) {
    for (int i = 0; i < container.length(); i++) {
        if (i > 0) {
            auto current = reinterpret_cast<std::uintptr_t>(&container.at(i));
            auto previous = reinterpret_cast<std::uintptr_t>(&container.at(i - 1));

            auto distance = current - previous;

            qInfo() << i << "At " << current << " previous " << previous << " distance " << distance;
        } else {
            qInfo() << i << &container.at(i) << " distance 0";
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<int> vect = QVector<int>();
    QList<int> list = QList<int>();

    fill(vect);
    fill(list);

    qInfo() << "int takes " << sizeof (int) << " bytes of ram";
    qInfo() << "Qvector uses continuous locations in memory";
    display(vect);

    qInfo() << "int takes " << sizeof (int) << " bytes of ram";
    qInfo() << "QList does not use continuous locations in memory";
    display(list);

    return a.exec();
}
