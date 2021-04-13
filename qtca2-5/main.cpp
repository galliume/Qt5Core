#include <QCoreApplication>
#include "client.h"
#include <QTcpSocket>

// /!\ add <QT += network> to project file

/**
 * For windows, install OpenSSL (https://slproweb.com/products/Win32OpenSSL.html)
 *
 * then in project file :
 *   MSVC_PATH  = "C:\Qt\5.15.2\mingw81_64"
 *   LIBS += -L$$MSVC_PATH/../../Tools/OpenSSL/Win_x64/lib -llibcrypto -llibssl
 *   INCLUDEPATH+= $$MSVC_PATH/../../Tools/OpenSSL/Win_x64/include
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    //client.connectToHost("httpbin.org", 80);
    client.connectToHost("httpbin.org", 443);

    QTcpSocket socket;
    socket.connectToHost("voidrealms.com", 80);
    qInfo() << "Connecting";

    if (socket.waitForConnected(50000)) {
        qInfo() << "Connected sending request";

        QByteArray data;
        data.append("GET /get HTTP/1.1\r\n");
        data.append("Host: local\r\n");
        data.append("Connection: Close\r\n");
        data.append("\r\n");

        socket.write(data);
        socket.waitForBytesWritten();

        if (socket.waitForReadyRead(10000)) {
            QByteArray response = socket.readAll();
            qInfo() << "Response " << response.length() << " bytes";
        }

        //socket.close();
        socket.waitForDisconnected();
        qInfo() << "Done";
    } else {
        qInfo() << socket.errorString();
    }

    return a.exec();
}
