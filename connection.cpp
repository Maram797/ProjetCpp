#include "connection.h"

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

Connection& Connection::createInstance()
{
    static Connection instance;
    return instance;
}

bool Connection::createConnection()
{
    // Source ODBC utilisateur 64 bits configuree dans Windows.
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("slim");
    db.setPassword(qEnvironmentVariable("DB_PASSWORD"));

    if (db.open()) {
        qDebug() << "Connexion etablie";
        return true;
    }

    qDebug() << "Echec de la connexion :" << db.lastError().text();
    return false;
}
