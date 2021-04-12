#include <QCoreApplication>
#include <QDebug>
#include <QSysInfo>
#include <QDir>
#include <QProcess>
#include <QStringList>
#include "commander.h"

bool test() {
    QProcess gzip;
    gzip.start("gzip", QStringList() << "-c");

    if (!gzip.waitForStarted()) return false;

    gzip.write("Qt rocks");
    gzip.closeWriteChannel();

    if (!gzip.waitForFinished()) return false;

    QByteArray result = gzip.readAll();
    qInfo() << "result " << result;

    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSysInfo sys;

    qInfo() << "System info";
    qInfo() << "Boot id " << sys.bootUniqueId();
    qInfo() << "Build " << sys.buildAbi();
    qInfo() << "CPU " << sys.buildCpuArchitecture();
    qInfo() << "Kernel " << sys.kernelType();
    qInfo() << "version " << sys.kernelVersion();
    qInfo() << "MAc " << sys.macVersion();
    qInfo() << "windows " << sys.windowsVersion();
    qInfo() << "host " << sys.prettyProductName();
    qInfo() << "type " << sys.productType();
    qInfo() << "version " << sys.productVersion();

#ifdef Q_OS_LINUX
    qInfo() << "Linux";
#elif defined(Q_OS_WIN32)
    qInfo() << "Windows";
#elif defined(Q_OS_MACX)
    qInfo() << "Mac";
#else
    qInfo() << "unknown";
#endif

    if (test()) {
        qInfo() << "Compressed with gzip";
    } else {
        qInfo() << "failed to use gzip";
    }

    qInfo() << "Starting";
    QProcess proc;
    const QString program = "notepad";
    const QStringList arguments;

    proc.execute(program, arguments);

    qInfo() << "Exit code " << proc.exitCode();


    commander cmd;
    cmd.action(QByteArray("echo %cd%"));//works only for windows, test purpose...
    cmd.action(QByteArray("dir"));//works only for windows, test purpose...

    return a.exec();
}
