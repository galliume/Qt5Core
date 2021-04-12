#include <QCoreApplication>

#include <QDebug>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaClassInfo>
#include <QTimer>
#include <QVariant>

#include "test.h"

void listProperties(QObject *obj) {
    for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
        QMetaProperty p = obj->metaObject()->property(i);
        qInfo() << "property " << p.name() << " " << p.typeName() << p.read(obj);
    }
}

void listMethods(QObject *obj) {
    for (int i = 0; i < obj->metaObject()->methodCount(); i++) {
        QMetaMethod m = obj->metaObject()->method(i);
        qInfo() << "method " << m.methodSignature();
    }
}

void listChildren(QObject *obj) {
    qInfo() << "object " << obj;

    foreach (QObject *child, obj->children()) {
        qInfo() << child;
        listMethods(child);
        listProperties(child);
        qInfo() << "";
    }
}

void testProp(QObject *parent, QString name, QVariant value) {
    foreach (QObject *child, parent->children()) {
        child->setProperty(name.toLatin1(), value);
    }
}

void listClassInfo(QObject *obj) {
    qInfo() << obj->metaObject()->className();

    for (int i = 0; i < obj->metaObject()->classInfoCount(); i++) {
        QMetaClassInfo c = obj->metaObject()->classInfo(i);
        qInfo() << "Property " << c.name() << " " << c.value();
    }
}

void pointerTest(QObject *obj) {
    qInfo() << obj;
}

void referenceTest(QObject &obj) {
    qInfo() << &obj;
}

void copyTest(QObject obj) {
    qInfo() << &obj;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject parent;
    QTimer *t = new QTimer(&parent);

    testProp(&parent, "interval", 3000);

    for (int i = 0; i < 5; i++) {
        test *t = new test(&parent);
        t->setObjectName("child " + QString::number(i));
    }

//    foreach (QObject *c, parent.children()) {
//        qInfo() << c;
//        qInfo() << c->metaObject()->className();
//        qInfo() << "inherit " << c->inherits("test");

//       for (int j = 0; j < c->metaObject()->methodCount(); j++) {
//           qInfo() << "methods " << c->metaObject()->method(j).methodSignature();
//       }

//       qInfo() << "";
//    }

    listChildren(&parent);

    test t1;
    listClassInfo(&t1);

    pointerTest(&t1);
    referenceTest(t1);
    //copyTest(t1); nop copy disabled

    return a.exec();
}
