#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    connect(&server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::start()
{
    server.listen(QHostAddress::Any, 2020);
}

void Server::quit()
{
    server.close();
}

void Server::newConnection()
{
    //same thread only
    QTcpSocket* socket = server.nextPendingConnection();

    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);

    qInfo() << "Connected " << socket;
}

void Server::disconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    qInfo() << "Disconnected " << socket;
    qInfo() << "Parent " << socket->parent();

    socket->deleteLater();
    //delete socket;
}

void Server::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    qInfo() << "readyRead " << socket;
    qInfo() << socket->readAll();
}
