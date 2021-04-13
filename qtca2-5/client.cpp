#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);

    connect(&socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);
}

void Client::connectToHost(QString host, quint16 port)
{
    if (socket.isOpen()) disconnect();

    qInfo() << "Connecting to " << host << " :: " << port;

    socket.connectToHost(host, port);
}

void Client::disconnect()
{
    socket.close();
}

void Client::connected()
{
    socket.write("HELLO\r\n");

    qInfo() << "Socket connected";

}

void Client::disconnected()
{
    qInfo() << "Socket closed";
}

void Client::error(QAbstractSocket::SocketError socketError)
{
    qInfo() << "Error " << socketError << " " << socket.errorString();
}

void Client::stateChanged(QAbstractSocket::SocketState socketState)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State " << metaEnum.valueToKey(socketState);
}

void Client::readyRead()
{
    qInfo() << "Data from " << sender() << "bytes " << socket.bytesAvailable();

    qInfo() << "Data " << socket.readAll();
}
