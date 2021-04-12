#include "logger.h"

QString logger::filename = QDir::currentPath() + QDir::separator() + "log.txt";
bool logger::logging = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

logger::logger()
{

}

void logger::attach()
{
    logger::logging = true;
    qInstallMessageHandler(logger::handler); //attach our msg handler
}

void logger::handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{

    if (logger::logging) {
        QString txt;

        switch (type) {
        case QtInfoMsg:
            txt = QString("Info: %1").arg(message);
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

        QFile file(logger::filename);

        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream txtStream(&file);
            txtStream << QDateTime::currentDateTime().toString() << " - " << txt << " file: " << context.file << " line: " << context.line << Qt::endl;
            txtStream.flush();
            file.close();
        }
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, message);//pass it back to default handler
}
