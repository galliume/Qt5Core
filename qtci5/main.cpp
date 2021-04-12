#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

void lhandler(QtMsgType type, const QMessageLogContext &context, const QString &message) {

    QString txt;

    switch (type) {
    case QtInfoMsg:
        txt = QString("Info: %1 in %2").arg(message);
        break;
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(message);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(message);
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(message);
        break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(message);
        break;
    }

    QFile file("log.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream txtStream(&file);
        txtStream << QDateTime::currentDateTime().toString() << " - " << txt << " file: " << context.file << " line: " << context.line << "\r\n";
        txtStream.flush();
        file.close();
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, message);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInstallMessageHandler(lhandler);

    qInfo() << "info";
    qDebug() << "debug";
    qWarning() << "warning";
    qCritical() << "critical";
    qFatal("fatal");

    return a.exec();
}
