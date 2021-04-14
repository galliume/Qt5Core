#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    pool.setMaxThreadCount(5);
}

void Server::start(quint16 port)
{
    qInfo() << this << " start " << QThread::currentThread();

    if (this->listen(QHostAddress::Any, port)) {
        qInfo() << " server started on " << port;
    } else {
        qCritical() << this->errorString();
    }
}

void Server::quit()
{
    this->close();
    qInfo() << "quit";
}

void Server::incomingConnection(qintptr handle)
{
    //  /!\ depends on qt version... check doc !
    qInfo() << "Incomming connection " << handle << " on " << QThread::currentThread();

    Client* client = new Client(nullptr, handle);
    client->setAutoDelete(true);
    pool.start(client);

}
