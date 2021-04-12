#ifndef TEST_H
#define TEST_H

#include <QObject>

class test : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Galliume")
    Q_CLASSINFO("url", "https://github.com/galliume")
    Q_DISABLE_COPY(test)
public:
    explicit test(QObject *parent = nullptr);

    void dostuff();
    void dostuff(QString param);
signals:
    void mysignal();
public slots:
    void myslot();
};

#endif // TEST_H
