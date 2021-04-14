#include <QCoreApplication>

#include <QGenericPlugin>
#include <QGenericPluginFactory>
#include <QDebug>

#include "../myplugin/iTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "Loading myplugin";

    QObject* plugin = QGenericPluginFactory::create("myplugin", "text");

    qInfo() << plugin;

    if (plugin) {
        iTest* myplugin = qobject_cast<iTest*>(plugin);

        if (myplugin) {
            myplugin->test();
        } else {
            qInfo() << "can't cast plugin";
        }

    } else {
        qInfo() << "could not load plugin";
    }

    return a.exec();
}
