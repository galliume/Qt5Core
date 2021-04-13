#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QUdpSocket>
#include <QNetworkDatagram>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
public slots:
    void start();
    void stop();
    void timeout();
    void readyRead();
    void broadcast();

private:
    QUdpSocket socket;
    QTimer timer;
    quint16 port = 2020;
};

#endif // WORKER_H
