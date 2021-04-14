#ifndef MYLIB_H
#define MYLIB_H

#include <QObject>
#include <QtPlugin>
#include <QDebug>
#include <QString>

#include "mylib_global.h"
#include "plugin.h"

class MYLIB_EXPORT Mylib : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.galliume.plugin")
    Q_INTERFACES(Plugin)

public:
    explicit Mylib(QObject* parent = nullptr);

    // Plugin interface
public:
    void test(QString name);
};

#endif // MYLIB_H
