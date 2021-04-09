#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QDir>

bool createDir(QString path) {

    QDir dir(path);

    if (dir.exists()) {
        qInfo() << "it already exists";
        return true;
    }

    if (dir.mkpath(path)) {
        qInfo() << "created";
        return true;
    } else {
        qInfo() << "could not create dir";
        return false;
    }
}

bool rename(QString path, QString name) {
    QDir dir(path);

    if (!dir.exists(path)) {
        qInfo() << "Path does not exist";
        return false;
    }

    int pos = path.lastIndexOf(QDir::separator());

    QString parent = path.mid(0, pos);
    QString newpath = parent + QDir::separator() + name;

    qInfo() << "Absolute " << dir.absolutePath();
    qInfo() << "Parent " << parent;
    qInfo() << "New " << newpath;

    return dir.rename(path, newpath);
}

bool remove(QString path) {
    qInfo() << "Removing " << path;

    QDir dir(path);

    if (!dir.exists()) {
        qInfo() << "Path does not exist";
        return false;
    }

    return dir.removeRecursively();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = QDir::currentPath();
    QString test = path + QDir::separator() + "test";
    QString tmp = path + QDir::separator() + "tmp";

    QDir current(QDir::currentPath());

    if (current.exists()) {
        foreach (QFileInfo fi, current.entryInfoList()) {
            qInfo() << fi.fileName();
        }
    }

    if (createDir(test)) {
        qInfo() << "Created test";

        if (rename(test, "tmp")) {
            qInfo() << "Renamed to tmp";

            if (remove(tmp)) {
                qInfo() << "Removed tmp";
            }
        }
    }

    return a.exec();
}
