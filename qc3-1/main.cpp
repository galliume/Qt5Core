#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QStringList>
#include <QRandomGenerator>

void saveAge(QSettings* settings, QString group, QString name, int age) {
    settings->beginGroup(group);
    settings->setValue(name, age);
    settings->endGroup();
}

int getAge(QSettings* settings, QString group, QString name) {
    settings->beginGroup(group);

    if (!settings->contains(name)) {
        qWarning() << "Settings does not contain " << group << " : " << name;
        settings->endGroup();
        return 0;
    }

    bool ok;
    int value = settings->value(name).toInt(&ok);
    settings->endGroup();

    if (!ok) {
        qWarning() << "Failed to convert to int";
        settings->endGroup();
        return 0;
    }

    return value;
}

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
    //qInfo() << settings.value("test").toString();
    //qInfo() << settings.value("test").toInt();

//    saveAge(&settings, "people", "tintin", 16);
//    saveAge(&settings, "whisky", "bowmore", 12);
//    saveAge(&settings, "whisky", "tintin", 2);

//    qInfo() << getAge(&settings, "people", "tintin");
//    qInfo() << getAge(&settings, "whisky", "bowmore");
//    qInfo() << getAge(&settings, "whisky", "tintin");

    QStringList people;
    people << "Tintin" << "Titi" << "Doc";

    foreach (QString person, people) {
        int value = QRandomGenerator::global()->bounded(100);
        saveAge(&settings, "test", person, value);
    }

    settings.sync();

    qInfo() << settings.fileName();

    foreach (QString group, settings.childGroups()) {
        settings.beginGroup(group);
        qInfo() << "Group: " << group;

        foreach (QString key, settings.childKeys()) {
            qInfo() << "....key " << key << settings.value(key).toString();
        }
        settings.endGroup();
    }

    return a.exec();
}
