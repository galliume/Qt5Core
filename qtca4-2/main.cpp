#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>
#include <QVariant>

/**
 *  For MariaDB :
 *
 *   Install Qt source (via qt maintenance tool)
 *   Install MariaDB with source
 *
 *   then :
 *
 *      cd C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers
 *      qmake sqldrivers.pro
 *      qmake -- MYSQL_INCDIR="C:/Program Files/MariaDB 10.5/include/mysql" MYSQL_LIBDIR="C:/Program Files/MariaDB 10.5/lib/"
 *      mingw32-make
 *      mingw32-make install
 *
 *  and copy C:\Program Files\MariaDB 10.5\lib\libmariadb.dll to C:\Qt\5.15.2\mingw81_64\bin
 */

void connectDB() {
    qInfo() << "connecting to db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMARIADB");

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("qtcore");
    db.setUserName("qtcore"); //should be in a separate file, but for testing purpose...
    db.setPassword("qtcore");

    if (!db.open()) {
        qInfo() << "Failed";
        qInfo() << db.lastError().text();
        return;
    }

    qInfo() << "Connected";

    db.close();
}

bool testPlugin() {
    qInfo() << "Testing plugin";
    QPluginLoader loader("C:/Qt/5.15.2/mingw81_64/plugins/sqldrivers/qsqlodbc.dll");

    qInfo() << loader.metaData();

    if (loader.load()) {
        qInfo() << "loaded sql plugin";
        return true;
    } else {
        qInfo() << loader.errorString();
        return false;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    foreach (QString driver, QSqlDatabase::drivers()) {
        qInfo() << driver;
        QSqlDatabase db = QSqlDatabase::addDatabase(driver);
        QSqlDriver *obj = db.driver();

        qInfo() << "\t Transactions: " << obj->hasFeature(QSqlDriver::DriverFeature::Transactions);
        qInfo() << "\t QuerySize: " << obj->hasFeature(QSqlDriver::DriverFeature::QuerySize);
        qInfo() << "\t BLOB: " << obj->hasFeature(QSqlDriver::DriverFeature::BLOB);
        qInfo() << "\t Unicode: " << obj->hasFeature(QSqlDriver::DriverFeature::Unicode);
        qInfo() << "\t PreparedQueries: " << obj->hasFeature(QSqlDriver::DriverFeature::PreparedQueries);
        qInfo() << "\t NamedPlaceholders: " << obj->hasFeature(QSqlDriver::DriverFeature::NamedPlaceholders);
        qInfo() << "\t PositionalPlaceholders: " << obj->hasFeature(QSqlDriver::DriverFeature::PositionalPlaceholders);
        qInfo() << "\t LastInsertId: " << obj->hasFeature(QSqlDriver::DriverFeature::LastInsertId);
        qInfo() << "\t BatchOperations: " << obj->hasFeature(QSqlDriver::DriverFeature::BatchOperations);
        qInfo() << "\t SimpleLocking: " << obj->hasFeature(QSqlDriver::DriverFeature::SimpleLocking);
        qInfo() << "\t LowPrecisionNumbers: " << obj->hasFeature(QSqlDriver::DriverFeature::LowPrecisionNumbers);
        qInfo() << "\t EventNotifications: " << obj->hasFeature(QSqlDriver::DriverFeature::EventNotifications);
        qInfo() << "\t FinishQuery: " << obj->hasFeature(QSqlDriver::DriverFeature::FinishQuery);
        qInfo() << "\t MultipleResultSets: " << obj->hasFeature(QSqlDriver::DriverFeature::MultipleResultSets);
        qInfo() << "\t CancelQuery: " << obj->hasFeature(QSqlDriver::DriverFeature::CancelQuery);
    }

    if (testPlugin()) {
        connectDB();
    }

    return a.exec();
}
