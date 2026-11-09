#include "connection.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QSqlError>

namespace {
void configureOracleClient()
{
    const QString appDirectory = QCoreApplication::applicationDirPath();
    if (QFile::exists(QDir(appDirectory).filePath("sqlnet.ora")))
        qputenv("TNS_ADMIN", appDirectory.toLocal8Bit());
}
}

Connection::Connection()
{
    configureOracleClient();
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

Connection &Connection::createInstance()
{
    static Connection connection;
    return connection;
}

bool Connection::createConnection()
{
    if (db.isOpen())
        return true;

    db.setDatabaseName("Source_Projet2A");
    db.setUserName("PAWCHE_2");
    db.setPassword("1234");
    return db.open();
}

QString Connection::lastError() const
{
    return db.lastError().text();
}
