#include <QCoreApplication>

#include <QDebug>
#include <QtConcurrent>
#include <QSharedPointer>
#include <QTextStream>

#include "manager.h"


/*
 * prefered way : QFutureWatcher
 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Manager manager;

    QTextStream cin(stdin);

    qInfo() << "Type START to begin";
    qInfo() << "Type QUIT to quit";

    do {

        QString command;
        cin >> command;

        if (command.toUpper() == "START") {
            manager.process();
        }

        if (command.toUpper() == "QUIT") {
            manager.quit();
        }

    } while(true);

    return a.exec();
}
