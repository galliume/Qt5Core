#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QDebug>

class source : public QObject
{
    Q_OBJECT
public:
    explicit source(QObject *parent = nullptr);
    void test();

signals:
    void mySignal(QString message);

public slots:

};

#endif // SOURCE_H
