#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDateTime>
#include <QDir>
#include <QStorageInfo>
#include <QIODevice>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QRandomGenerator>
#include <QLockFile>

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

void list(QString path) {
    qInfo() << "Listing : " << path;

    QDir dir(path);
    qInfo() << dir.absolutePath();

    QFileInfoList dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList files = dir.entryInfoList(QDir::Files);

    foreach (QFileInfo fi, dirs) {
        qInfo() << fi.fileName();
    }

    foreach(QFileInfo fi, files) {
        qInfo() << "..Name " << fi.fileName();
        qInfo() << "..Size " << fi.size();
        qInfo() << "..Created " << fi.birthTime();
        qInfo() << "..Modified " << fi.lastModified();
    }

    foreach(QFileInfo fi, files) {
        list(fi.absoluteFilePath());
    }
}

bool put(QString path, QByteArray data, QIODevice::OpenMode mode) {

    QFile file(path);

    if (!file.open(mode)) {
        qWarning() << file.errorString();
        return false;
    }

    qint64 bytes = file.write(data);

    if(!bytes) {
        qWarning() << file.errorString();
    } else {
        qInfo() << "Wrote " << bytes;
    }

    file.flush();//not really needed but to be sure
    file.close();

    return true;
}

void write(QString path, QByteArray data) {
    qInfo() << "Write to file";

    if (put(path, data, QIODevice::WriteOnly)) {
        qInfo() << "Data written to file";
    } else {
        qWarning() << "Failed to write";
    }
}

void append(QString path, QByteArray data) {
    qInfo() << "Write to file";

    if (put(path, data, QIODevice::Append)) {
        qInfo() << "Data written to file";
    } else {
        qWarning() << "Failed to write";
    }
}

bool writeBis(QString path, QByteArray data) {
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << file.errorString();
        return false;
    }

    qint64 bytes = file.write(data);
    file.close();

    return (bytes) ? true : false;
}

bool createFile(QString path) {
    QByteArray data;
    for (int i = 0; i < 5; i++) {
        data.append(QString::number(i));
        data.append(" Hello world \r\n");
    }

    return writeBis(path, data);
}

void readFile(QString path) {
    QFile file(path);

    if (!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
    }

    qInfo() << "..Reading file ";
    qInfo() << file.readAll();
    qInfo() << "..Done ";

    file.close();
}

void readLines(QString path) {
    QFile file(path);

    if (!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
    }

    qInfo() << "..Reading file ";
    while(!file.atEnd()) {
        QString line(file.readLine());
        qInfo() << line.trimmed();
    }
    qInfo() << "..Done ";
    file.close();
}

void readBytes(QString path) {
    QFile file(path);

    if (!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
    }

    qInfo() << "..Reading file ";
    while(!file.atEnd()) {
        qInfo() << file.read(5);
    }
    qInfo() << "..Done ";
    file.close();
}

bool createFileStream(QString path) {
    QFile file(path);

    if (!file.exists()) {
        qWarning() << "File not found";
        return false;
    }

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << file.errorString();
    }

    //QDataStream stream(&file); //convert everything into an encoding
    QTextStream stream(&file); //work with text
    int max = 1000;
    QString banner = "Random number \r\n";
    qInfo() << "Writting " << banner;

    stream << banner;

    for (int i = 0; i < 5; i++) {
        qint32 num = QRandomGenerator::global()->bounded(max);
        qInfo() << "Writting " << num;
        stream << num << "\r\n";
    }

    file.close();

    return true;
}

void readFileStream(QString path) {
    QFile file(path);

    if (!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
    }

    //QDataStream stream(&file);
    QTextStream stream(&file);

    QString banner;
    stream >> banner;

    qInfo() << "Banner :" << banner;

    for (int i = 0; i < 5; i++) {
        //qint32 num;
        QString num;
        stream >> num ;

        qInfo() << "Random : " << num;
    }

    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QString path = QDir::currentPath();
//    QString test = path + QDir::separator() + "test";
//    QString tmp = path + QDir::separator() + "tmp";

//    QDir current(QDir::currentPath());

//    if (current.exists()) {
//        foreach (QFileInfo fi, current.entryInfoList()) {
//            qInfo() << fi.fileName();
//        }
//    }

//    if (createDir(test)) {
//        qInfo() << "Created test";

//        if (rename(test, "tmp")) {
//            qInfo() << "Renamed to tmp";

//            if (remove(tmp)) {
//                qInfo() << "Removed tmp";
//            }
//        }
//    }

    //list(QDir::tempPath());

//    foreach (QStorageInfo storage, QStorageInfo::mountedVolumes()) {
//        qInfo() << "Name " << storage.displayName();
//        qInfo() << "type " << storage.fileSystemType();
//        qInfo() << "Total " << storage.bytesTotal()/1000/1000 << "MB";
//        qInfo() << "Available " << storage.bytesAvailable()/1000/1000 << "MB";
//        qInfo() << "Device " << storage.displayName();
//        qInfo() << "Root " << storage.isRoot();
//        qInfo("---");
//    }

//    QStorageInfo root = QStorageInfo::root();
//    QDir dir(root.rootPath());

//    foreach (QFileInfo fi, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
//        qInfo() << fi.filePath();
//    }

//    QString path = QDir::currentPath() + QDir::separator() + "test.txt";
//    qInfo() << "path: " << path;

//    QByteArray data("Hello world \r\n");

//    for (int i = 0; i < 5; i++) {
//        QString num = QString::number(i);
//        num.append(" ");

//        QByteArray line(num.toLatin1() + data);

//        append(path, line);
//    }

//    QString path = QDir::currentPath() + QDir::separator() + "test.txt";
//    qInfo() << "Path " << path;

//    if (createFile(path)) {
//        readFile(path);
//        readLines(path);
//        readBytes(path);
//    }

//    QString path = QDir::currentPath() + QDir::separator() + "test.txt";
//    qInfo() << "Path " << path;

//    if (createFileStream(path)) {
//        readFileStream(path);
//    }

    qInfo() << "Attempting to lock a file";

    QFile file(QDir::currentPath() + QDir::separator() + "test.txt");
    QLockFile lock(file.fileName() + "l");
    lock.setStaleLockTime(30000);//ms

    if (lock.tryLock()) {
        if (file.open(QIODevice::WriteOnly)) {
            QByteArray data;
            file.write(data);
            file.close();
        }
        qInfo() << "unlocking";
        lock.unlock();
    } else {
        qInfo() << "Could not lock";
        qint64 pid;
        QString host;
        QString application;

        if (lock.getLockInfo(&pid, &host, &application)) {
            qInfo() << "File is locked by " << pid << " " << " " << host << " " << application;
        } else {
            qInfo() << "Locked by unknown";
        }
    }

    return a.exec();
}
