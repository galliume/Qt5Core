#include <QCoreApplication>
#include <QDebug>
#include <QUdpSocket>
#include <QDateTime>
#include <QNetworkDatagram>

bool bind(QUdpSocket* socket, quint16 port) {

    //if (socket->bind(port, QUdpSocket::ShareAddress)) { //ignored on windows
    //if (socket->bind(port, QUdpSocket::DontShareAddress)) {
    if (socket->bind(port, QUdpSocket::ReuseAddressHint)) { //windows
        return true;
    }

    qInfo() << socket->errorString();
    return false;
}

void send(QUdpSocket* socket, quint16 port) {
    QString date = QDateTime::currentDateTime().toString();
    QByteArray data = date.toLatin1();

    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port); //network

    qInfo() << "Sending";


    if (socket->writeDatagram(datagram) <= 0) {
        qInfo() << socket->errorString();
    }
}

void read(QUdpSocket* socket) {

    qInfo() << "Reading";

    socket->waitForReadyRead(10000);
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        qInfo() << datagram.data();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUdpSocket broadcaster;
    QUdpSocket client;

    quint16 port = 2020;

    qInfo() << "Binding";

    if (bind(&broadcaster, port) && bind(&client, port)) {
        send(&broadcaster, port);
        read(&client);
    } else {
        qInfo() << "can't bind";
    }

    return a.exec();
}
