#include <QCoreApplication>
#include "client.h"

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

    return a.exec();
}
