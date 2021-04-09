#include <QCoreApplication>
#include <QIODevice>
#include <QBuffer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QBuffer buffer;

    if (buffer.open(QIODevice::ReadWrite)) {
        qInfo() << "Buffer opened";

        QByteArray data("Hello world");

        for (int i = 0; i < 5; i++) {
            buffer.write(data);
            buffer.write("\r\n");
        }

        //buffer.flush();
        buffer.seek(0);

        qInfo() << buffer.readAll();

        qInfo() << "closing the buffer";
        buffer.close();

    } else {
        qInfo() << "Could not open buffer";
    }

    return a.exec();
}
