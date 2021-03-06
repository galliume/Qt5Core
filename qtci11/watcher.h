#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFileSystemWatcher>

class watcher : public QObject
{
    Q_OBJECT
public:
    watcher();
public slots:
    void fileChanged(const QString &path);
    void directoryChanged(const QString &path);

private:
    QFileSystemWatcher fsw;
};

#endif // WATCHER_H
