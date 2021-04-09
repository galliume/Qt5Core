#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Galliume");
    QCoreApplication::setOrganizationDomain("Galliume.io");
    QCoreApplication::setApplicationName("Tester");

    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    //save a setting
    //On windows : write on registry
    //on linux : write on file
    //must encrypt data ourself
    //settings.setValue("test", 123);

    //read
    qInfo() << settings.value("test").toString();
    qInfo() << settings.value("test").toInt();

    return a.exec();
}
