#include <QCoreApplication>
#include <QHash>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QHash<QString, int>ages;
    ages.insert("Rintintin", 5);
    ages.insert("Fido", 3);
    ages.insert("Milo", 6);

    qInfo() << "Rintintin " << ages["Rintintin"];
    qInfo() << "keys " << ages.keys();
    qInfo() << "size " << ages.size();

    foreach (QString key, ages.keys()) {
        qInfo() << key << " : " << ages[key];
    }

    return a.exec();
}
