#include <QCoreApplication>
#include <QFuture>
#include <QtConcurrent>

#include "commandline.h"
#include "chat.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Commandline cli(&a, stdin);
    QFuture<void> future = QtConcurrent::run(&cli, &Commandline::monitor);

    Chat chat;
    QObject::connect(&cli, &Commandline::command, &chat, &Chat::command, Qt::QueuedConnection);

    qInfo() << "Enter your name ";

    return a.exec();
}
