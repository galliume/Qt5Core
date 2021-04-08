#include <QCoreApplication>

#include <QTextStream>
#include <iostream>

#include "radio.h"
#include "station.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    radio boombox;

    station* channels[3];
    channels[0] = new station(&boombox, 10, "Rock");
    channels[1] = new station(&boombox, 15, "News");
    channels[2] = new station(&boombox, 15, "Electro");

    //Qt::QueuedConnection -> work with threads
    //connect boombox with quit app
    boombox.connect(&boombox, &radio::quit, &a, &QCoreApplication::quit, Qt::QueuedConnection);

    do {
        qInfo() << "Enter on, off, test or quit";

        //read stdin with qt text stream
        QTextStream qtin(stdin);
        QString line = qtin.readLine().trimmed().toUpper();

        if (line == "ON") {
            qInfo() << "Turning radio on";

            for (int i = 0; i < 3; i++) {
                station* channel = channels[i];
                boombox.connect(channel, &station::send, &boombox, &radio::listen);
            }

            qInfo() << "Radio is on";
        }

        if (line == "OFF") {
            qInfo() << "Turning radio off";

            for (int i = 0; i < 3; i++) {
                station* channel = channels[i];
                boombox.disconnect(channel, &station::send, &boombox, &radio::listen);
            }

            qInfo() << "Radio is off";
        }

        if (line == "TEST") {
            qInfo() << "Testing";

            for (int i = 0; i < 3; i++) {
                station* channel = channels[i];
                channel->broacast("Broadcasting live");
            }

            qInfo() << "Testing complete";
        }

        if (line == "QUIT") {
            qInfo() << "Quiting";

            emit boombox.quit();
            break;
        }

    } while(true);


    return a.exec();
}
