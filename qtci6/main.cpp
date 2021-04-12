#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QRandomGenerator>
#include <QTextCodec>

QByteArray makeData() {
    QByteArray data;

    for (int i = 0; i < 10; i++) {
        data.append(72);
        data.append(101);
        data.append(108);
        data.append(108);
        data.append(111);
        data.append(33);
        data.append(13);
        data.append(10);
    }
    return data;
}

QString makeDataUnicode() {
    QString data;

    data.append("Unicode test \r\n");

    for (int i = 0; i < 10; i++) {
        int number = QRandomGenerator::global()->bounded(1112064);
        data.append(number);
    }

    data.append("\r\n");

    return data;
}

QString makeDataBase64() {
    QString data;

    data.append("Unicode test \r\n");

    for (int i = 0; i < 10; i++) {
        data.append("Hello \r\n");
    }

    data.append("\r\n");

    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QByteArray data = makeData();
    QString data = makeDataUnicode();

    QString path = QDir::currentPath() + QDir::separator() + "test.txt";
    QFile file(path);

    if (file.open(QIODevice::WriteOnly)) {

        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream << data;
        stream.flush();

        file.close();
    }

    qInfo() << "Done";
    qInfo() << "Unicode :" << data;
    qInfo() << "ASCII " << data.toLatin1();

    QString data64 = makeDataBase64();

    QTextCodec *codec = QTextCodec::codecForName("UTF-16");

    if (!codec) qFatal("No codec");

    QByteArray bytes = codec->fromUnicode(data);
    qInfo() << "Bytes : " << bytes;
    QString string = codec->toUnicode(bytes);
    qInfo() << "Bytes to unicode : " << bytes;

//    QByteArray bytes(data.toLatin1());
//    QByteArray encoded = bytes.toBase64();
//    QByteArray decoded = bytes.fromBase64(encoded);

//    qInfo() << "Encoded " << encoded;
//    qInfo() << "Decoded " << decoded;

    return a.exec();
}
