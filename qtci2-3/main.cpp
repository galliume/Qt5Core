#include <QCoreApplication>
#include <QSet>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSet<QString> people;// no specific order, very fast lookup for values
    people << "Tintin" << "Doc" << "Titi";
    people.insert("Neo");

    foreach (QString person, people) {
        qInfo() << person;
    }

    qInfo() << "Tintin in collection: " << people.contains("Tintin");

    return a.exec();
}
