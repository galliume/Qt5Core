#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{

    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &Worker::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &Worker::encrypted);
    //connect(&manager, &QNetworkAccessManager::networkAccessibleChanged, this, &Worker::networkAccessibleChanged);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Worker::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &Worker::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Worker::sslErrors);
}

void Worker::get(QString location)
{
    qInfo() << "Getting from server";
    QNetworkReply* replay = manager.get(QNetworkRequest(QUrl(location)));
    connect(replay, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::post(QString location, QByteArray data)
{
    qInfo() << "Posting to server";

    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    QNetworkReply* replay = manager.post(request, data);
    connect(replay, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::readyRead()
{
    qInfo() << "ReadyRead";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) qInfo() << reply->readAll();
}

void Worker::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qInfo() << "authenticationRequired";
}

void Worker::encrypted(QNetworkReply *reply)
{
    qInfo() << "encrypted";
}

void Worker::finished(QNetworkReply *reply)
{
    qInfo() << "finished";

}

void Worker::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qInfo() << "preSharedKeyAuthenticationRequired";

}

void Worker::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qInfo() << "proxyAuthenticationRequired";
}

void Worker::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qInfo() << "sslErrors";
}
