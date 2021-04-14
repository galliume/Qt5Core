#include <QCoreApplication>
#include <QDebug>

#include "server.h"

//openssl s_client -connect 127.0.0.1:2020

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.setKey("C:/Users/Guillaume/Documents/_workspace/Qt5Core/certs/server.key");
    server.setCert("C:/Users/Guillaume/Documents/_workspace/Qt5Core/certs/server.crt");

    if (!server.listen(QHostAddress::Any, 2020)) {
        qInfo() << server.errorString();
    } else {
        qInfo() << "Listening on " << server.serverAddress() << " " << server.serverPort();
    }

    return a.exec();
}
