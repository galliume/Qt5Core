#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);

    connect(&socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);

    QNetworkProxy proxy(QNetworkProxy::HttpProxy, "165.225.77.47", 9400);
//    proxy.setUser("galliume");
//    proxy.setPassword("password");
    //QNetworkProxy::setApplicationProxy(proxy);
    socket.setProxy(proxy);
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
    //socket.write("HELLO\r\n");
    qInfo() << "Socket sending";
    QByteArray data;
    data.append("GET /get HTTP/1.1\r\n");
    data.append("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    data.append("Host: local\r\n");
    data.append("Connection: Close\r\n");
    data.append("\r\n");
    socket.write(data);

    socket.waitForBytesWritten();
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
