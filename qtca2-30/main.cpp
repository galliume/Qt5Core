#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

#include "worker.h"


void upload(Worker* worker) {
    QString location = "ftp://speedtest.tele2.net/upload/galliume-" + QString::number(QDateTime::currentSecsSinceEpoch()) + ".jpg";
    QString path = "C:/Users/Guillaume/Documents/_workspace/Qt5Core/never-gonna-give-you-up-clip.jpg";

    worker->upload(location, path);
}

void download(Worker* worker) {
    QString location = "ftp://speedtest.tele2.net/512KB.zip";
    QString path = "C:/Users/Guillaume/Documents/_workspace/Qt5Core/512KB.zip";

    worker->download(location, path);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker;

    worker.get("https://postman-echo.com/get?foo1=bar&foo2=bar2");


    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=world");

    worker.post("https://postman-echo.com/post", data);

    //upload(&worker);
    download(&worker);

    return a.exec();
}
