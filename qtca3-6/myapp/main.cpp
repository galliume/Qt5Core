#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QPluginLoader>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>

#include "../mylib/mylib.h"

QStringList getPlugin(QString path) {
    QStringList filter;

    filter << "*.dll" << "*.so" << "*.dylib";

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filter);
    QStringList plugins;

    foreach (QFileInfo file, list) {
        plugins.append(file.filePath()); //check for symlink
    }

    return plugins;
}

void testPlugins(QStringList plugins) {
    foreach (QString file, plugins) {
        qInfo() << "loading "  << file;

        QPluginLoader loader(file);

        if (!loader.load()) {
            qInfo() << "Could not load " << loader.fileName() << " " << loader.errorString();
            continue;
        }

        qInfo() << "Plugin loaded " << loader.fileName();

        Plugin* plugin = qobject_cast<Plugin*>(loader.instance());

        if (plugin) {
            plugin->test("Guillaume");
        } else {
            qInfo() << "could not cast plugin " << loader.fileName();
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir dir = QDir::current();
    dir.cdUp();
    dir.cd("mylib/debug");

    qInfo() << "lib path " << dir.path();

    QStringList plugins = getPlugin(dir.path());
    qInfo() << "Plugins " << plugins;

    testPlugins(plugins);
    qInfo() << "done";

    return a.exec();
}
