#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QDebug>
#include <QProcess>

class commander : public QObject
{
    Q_OBJECT
public:
    commander();
    ~commander();
signals:
public slots:
    void readyRead();
    void action(QByteArray data);

private:
    QProcess proc;
    QString app;
    QString endl;

};

#endif // COMMANDER_H
