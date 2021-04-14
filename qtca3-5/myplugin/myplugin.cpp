#include "myplugin.h"

MyPlugin::MyPlugin(QObject *parent): QGenericPlugin(parent)
{
}

QObject *MyPlugin::create(const QString &name, const QString &spec)
{    
    return new MyPlugin;
}

void MyPlugin::test()
{
    qInfo() << "This as test of our plugin with an interface";
}


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(MyPlugin, MyPlugin)
#endif // QT_VERSION < 0x050000
