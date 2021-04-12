#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QBuffer>
#include <QTextStream>

QByteArray makeData() {
    QByteArray data;

    for (int i = 0; i < 1000; i++) {
        data.append(QString::number(i) + "\r\n");
    }
    return data;
}

bool makeFile(QString path) {

    QFile file(path);

    if (file.open(QIODevice::WriteOnly)) {

        QByteArray data;

        for (int i = 0; i < 1000; i++) {
            data.append(QString::number(i) + "\r\n");
        }

        file.write(data);
        file.close();
        return true;
    }
    return false;
}

QByteArray getHeader() {
    QByteArray header;

    header.append("@!~!@");

    return header;
}

bool compress(QString original, QString newFile) {
    QFile ofile(original);
    QFile nfile(newFile);
    QByteArray header = getHeader();

    if (!ofile.open(QIODevice::ReadOnly)) return false;
    if (!nfile.open(QIODevice::WriteOnly)) return false;

    int size = 1024;

    while (!ofile.atEnd()) {
        QByteArray buffer = ofile.read(size);
        QByteArray compressed = qCompress(buffer);

        qInfo() << "Header at : " << nfile.pos();

        nfile.write(header);

        qInfo() << "Size " << nfile.write(compressed);
    }

    ofile.close();
    nfile.close();

    return true;
}

bool decompress(QString original, QString newFile) {
    QFile ofile(original);
    QFile nfile(newFile);
    QByteArray header = getHeader();

    if (!ofile.open(QIODevice::ReadOnly)) return false;
    if (!nfile.open(QIODevice::WriteOnly)) return false;

    int size = 1024;

    QByteArray buffer = ofile.peek(size);

    if (!buffer.startsWith(header)) {
        qCritical() << "Not compressed";
        ofile.close();
        nfile.close();
        return false;
    }

    ofile.seek(header.length());
    qInfo() << "Starting at " << ofile.pos();

    while (!ofile.atEnd()) {
        buffer = ofile.peek(size);
        qint64 index = buffer.indexOf(header);

        qInfo() << "Header found at " << index;

        if (index > -1) {//have a header
            qint64 maxbytes = index;
            qInfo() << "Reading " << maxbytes;
            buffer = ofile.read(maxbytes);
            ofile.read(header.length());
        } else {// no header
            qInfo() << "Read all, no header";
            buffer = ofile.readAll();
        }

        QByteArray decompressed = qUncompress(buffer);
        qInfo() << "Decompressed " << nfile.write(decompressed);
        nfile.flush();
    }

    ofile.close();
    nfile.close();

    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray data = makeData();
    QByteArray compressed = qCompress(data);
    QByteArray decompressed = qUncompress(compressed);

    qInfo() << "Original " << data.length();
    qInfo() << "compressed " << compressed.length();
    qInfo() << "decompressed " << decompressed.length();


    QString originalFile = QDir::currentPath() + QDir::separator() + "orginal.txt";
    QString compressedFile = QDir::currentPath() + QDir::separator() + "compressed.txt";
    QString decompressedFile = QDir::currentPath() + QDir::separator() + "decompressed.txt";

    if (makeFile(originalFile)) {
        qInfo() << "Original created";

        if (compress(originalFile, compressedFile)) {
            qInfo() << "File compressed";

            if (decompress(compressedFile, decompressedFile)) {
                qInfo() << "File decompressed";
            } else {
                qInfo() << "COuld not decompress";
            }
        } else {
            qInfo() << "File not compressed";
        }
    }

    return a.exec();
}
