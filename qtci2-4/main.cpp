#include <QCoreApplication>
#include <QMap>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMap<QString, int>ages;//ordered, little slower than QSet
    ages.insert("Tintin", 25);
    ages.insert("Doc", 55);
    ages.insert("Titi", 6);

    qInfo() << "tintin is " << ages["Tintin"];
    qInfo() << "Keys " << ages.keys();

    foreach (QString key, ages.keys()) {
        qInfo() << key << " : " << ages[key];
    }

    return a.exec();
}
