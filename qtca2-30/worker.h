#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QFile>
#include <error.h>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:

public slots:
    void get(QString location);
    void post(QString location, QByteArray data);
    void upload(QString location, QString path);
    void download(QString location, QString path);

private slots:

    //HTTP
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);

    //obsolete
    //void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);

    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

    //FTP
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void error(QNetworkReply::NetworkError code);

    //BOTH
    void readyRead();
    void finished(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
    QFile file;

    void wire(QNetworkReply* reply);
};

#endif // WORKER_H
