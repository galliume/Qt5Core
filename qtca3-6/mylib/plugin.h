#ifndef PLUGIN_H
#define PLUGIN_H

#include <QString>
#include <QDebug>

class Plugin
{
public:
    virtual void test(QString name) = 0;
};

Q_DECLARE_INTERFACE(Plugin, "com.galliume.plugin")

#endif // PLUGIN_H
