#include "watcher.h"

watcher::watcher()
{
    fsw.addPath(QDir::currentPath());
    fsw.addPath(QDir::currentPath() + QDir::separator() + "test.txt");

    connect(&fsw, &QFileSystemWatcher::fileChanged, this, &watcher::fileChanged);
    connect(&fsw, &QFileSystemWatcher::directoryChanged, this, &watcher::directoryChanged);
}

void watcher::fileChanged(const QString &path)
{
    qInfo() << "File changed " << path;

    if (fsw.files().length()) {
        qInfo() << "Files that have changed";

        foreach (QString file, fsw.files()) {
            qInfo() << file;
        }
    }
}

void watcher::directoryChanged(const QString &path)
{
    qInfo() << "Directory changed " << path;

    if (fsw.files().length()) {
        qInfo() << "Directory changed";

        foreach (QString dir, fsw.directories()) {
            qInfo() << dir;
        }
    }
}
