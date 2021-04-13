#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    connect(&timer, &QTimer::timeout, this, &Worker::timeout);
    connect(&socket, &QUdpSocket::readyRead, this, &Worker::readyRead);

    timer.setInterval(1000);
}

void Worker::start()
{
    if (!socket.bind(port)) {
        qInfo() << socket.errorString();
        return;
    }

    qInfo() << "Start UDP on " << socket.localAddress() << " :: " << socket.localPort();

    broadcast();
}

void Worker::stop()
{
    timer.stop();
    socket.close();
    qInfo() << "Stop UDP";
}

void Worker::timeout()
{
    QString date = QDateTime::currentDateTime().toString();
    QByteArray data = date.toLatin1();

    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);

    qInfo() << "Send " << data;

    socket.writeDatagram(datagram);
}

void Worker::readyRead()
{
    while (socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "Read " << datagram.data() << " from " << datagram.senderAddress() << " " << datagram.senderPort();
    }
}

void Worker::broadcast()
{
    qInfo() << "Broadcast ";

    timer.start();
}
