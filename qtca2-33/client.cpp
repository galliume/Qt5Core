
#include "client.h"

Client::Client(QObject *parent, qintptr handle) : QObject(parent), QRunnable(), handle(handle)
{

}

void Client::run()
{
    qInfo() << this << " run " << QThread::currentThread();

    QTcpSocket* socket = new QTcpSocket(nullptr);//multithread => no parent

    if (!socket->setSocketDescriptor(handle)) {
        qCritical() << socket->errorString();
        delete socket;

        return;
    }

    socket->waitForReadyRead();
    QByteArray request = socket->readAll();

    qInfo() << " request " << request.length();

    QByteArray data("Hello World!");

    QByteArray response;
    response.append("HTTP/1.1 200 OK\r\n");
    response.append("Content-Type: text/plain\r\n");
    response.append("Content-Length: " + QString::number(data.length()) + "\r\n");
    response.append("Connection: close\r\n");
    response.append("\r\n");
    response.append(data);

    socket->write(response);
    socket->waitForBytesWritten();
    socket->close();
    socket->deleteLater();

    qInfo() << this << " done " << QThread::currentThread();
}
