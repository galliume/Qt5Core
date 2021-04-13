#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QtConcurrent>
#include <QThread>

class Commandline : public QObject
{
    Q_OBJECT
public:
    explicit Commandline(QObject *parent = nullptr, FILE* fileHandler = nullptr);

    [[noreturn]] void monitor();

signals:
    void command(QString value);

private:
    QTextStream cin;
};

#endif // COMMANDLINE_H
