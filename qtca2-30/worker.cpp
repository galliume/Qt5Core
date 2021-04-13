#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{

    //HTTP
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &Worker::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &Worker::encrypted);
    //connect(&manager, &QNetworkAccessManager::networkAccessibleChanged, this, &Worker::networkAccessibleChanged);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Worker::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &Worker::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Worker::sslErrors);

    //FTP
    connect(&manager, &QNetworkAccessManager::finished, this, &Worker::finished);
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

void Worker::upload(QString location, QString path)
{
    qInfo() << "Uploading " << path;

    file.setFileName(path);

    if (!file.open(QIODevice::ReadOnly)) {
        qInfo() << "Could not open file " << file.errorString();
        return;
    }

    QUrl url(location);
    //url.setPassword
    //url.setUsername
    //url.setPort

    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager.put(request, &file);

    wire(reply);
}

void Worker::download(QString location, QString path)
{
    qInfo() << "Downloading " << path;

    file.setFileName(path);

    if (!file.open(QIODevice::WriteOnly)) {
        qInfo() << "Could not open file " << file.errorString();
        return;
    }

    QUrl url(location);
    //url.setPassword
    //url.setUsername
    //url.setPort

    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager.get(request);

    wire(reply);
}

void Worker::readyRead()
{
    qInfo() << "ReadyRead";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    //if (reply) qInfo() << reply->readAll();
    //http and ftp worker should be two different class.

    if (reply) {
        QByteArray data = reply->readAll();
        file.write(data);//should add some checking on file
    }
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
    file.close();
    reply->close();

}

void Worker::wire(QNetworkReply *reply)
{
    connect(reply, &QNetworkReply::readyRead, this, &Worker::readyRead);
    connect(reply, &QNetworkReply::uploadProgress, this, &Worker::uploadProgress);
    connect(reply, &QNetworkReply::downloadProgress, this, &Worker::downloadProgress);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred), this, &Worker::error);
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

void Worker::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal <= 0) return;
    qInfo() << "Uploading " << bytesSent << " of " << bytesTotal;
}

void Worker::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal <= 0) return;
    qInfo() << "Downloading " << bytesReceived << " of " << bytesTotal;
}

void Worker::error(QNetworkReply::NetworkError code)
{

}
