#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

// /!\ add <QT += network> to the project file

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for (int i = 0; i < list.length(); i++) {
        QHostAddress address = list.at(i);

        qInfo() << address.toString();

        qInfo() << "\t loopback " << address.isLoopback();
        qInfo() << "\t multicast " << address.isMulticast();

        switch (address.protocol()) {

            case QAbstractSocket::UnknownNetworkLayerProtocol:
                qInfo() <<"\t Procotol unknown";
                break;

            case QAbstractSocket::AnyIPProtocol:
                qInfo() <<"\t Procotol Any";
                break;

            case QAbstractSocket::IPv4Protocol:
                qInfo() <<"\t Procotol IPV4";
                break;

            case QAbstractSocket::IPv6Protocol:
                qInfo() <<"\t Procotol IPV6";
                break;
        }

    }

    return a.exec();
}
