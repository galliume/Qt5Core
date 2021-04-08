#ifndef TEST_H
#define TEST_H

#include <QObject>

class test : public QObject
{
    Q_OBJECT
public:
    test();
    QString message();
    void setMessage(QString value);

    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
private:
    QString m_message;
signals:
    void messageChanged(QString message);
public slots:
};

#endif // TEST_H
