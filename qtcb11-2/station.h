#ifndef STATION_H
#define STATION_H

#include <QObject>

class station : public QObject
{
    Q_OBJECT
public:
    explicit station(QObject *parent = nullptr, int channel = 0, QString name = "unknown");
    QString name;
    int channel;

 signals:
    void send(int channel, QString name, QString message);

public slots:
    void broacast(QString message);
};

#endif // STATION_H
