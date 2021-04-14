#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QGenericPlugin>
#include <QDebug>

#include "iTest.h"

class MyPlugin : public QGenericPlugin, iTest
{
    Q_OBJECT
    Q_INTERFACES(iTest)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "MyPlugin.json")
#endif // QT_VERSION >= 0x050000

public:
    explicit MyPlugin(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;

    // iTest interface
public:
    void test() override;
};

#endif // MYPLUGIN_H
