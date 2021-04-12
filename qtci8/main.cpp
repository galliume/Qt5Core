#include <QCoreApplication>

#include <QDebug>
#include <QDataStream>
#include <QFile>
#include "test.h"
#include "converter.h"

bool saveFile(QString path) {
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) return false;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    QString title = "The answer is 42";
    qint64 num = 42;

    out << title;
    out << num;

    file.flush();
    file.close();

    return true;
}

bool readFile(QString path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) return false;

    QDataStream in(&file);
    if (in.version() != QDataStream::Qt_5_15) {
        qCritical() << "Bad version";
        file.close();
        return false;
    }

    QString title;
    qint64 num;

    in >> title;
    in >> num;

    qInfo() << title;
    qInfo() << num;

    return true;
}

bool saveFileSerialized(test *t, QString path) {
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) return false;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_5_15);
    ds << *t;

    file.close();
    return true;
}

bool readFileSerialized(QString path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) return false;

    QDataStream ds(&file);
    test t;
    ds >> t;

    file.close();

    qInfo() << "Name " << t.name();

    foreach (QString key, t.map().keys()) {
        qInfo() << key << " " << t.map().value(key);
    }

    return true;
}

void writeJson(QString path) {
    test t;
    t.fill();
    converter::writeJson(&t, path);
}

void readJson(QString path) {
    test *t;
    t = converter::readJson(path);

    if (!t) {
        qInfo() << "Object not loaded";
        return;
    }

    qInfo() << "Name " << t->name();

    foreach (QString key, t->map().keys()) {
        qInfo() << key << " " << t->map().value(key);
    }
}

void writeXml(QString path) {
    test t;
    t.fill();
    converter::writeXml(&t, path);
}

void readXml(QString path) {
    test *t;
    t = converter::readXml(path);

    if (!t) {
        qInfo() << "Object not loaded";
        return;
    }

    qInfo() << "Name " << t->name();

    foreach (QString key, t->map().keys()) {
        qInfo() << key << " " << t->map().value(key);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString file = "test.txt";

    if (saveFile(file)) {
        qInfo() << "saved";

        readFile(file);
    }


    test t;
    t.fill();

    if (saveFileSerialized(&t , "test2.txt")) {
        readFileSerialized("test2.txt");
    }

    QString path = "testJson.txt";

    writeJson(path);
    readJson(path);

    path = "testXml.txt";

    writeXml(path);
    readXml(path);

    return a.exec();
}
