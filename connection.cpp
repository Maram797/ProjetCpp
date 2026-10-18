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
    
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("slim");
    const QString password = qEnvironmentVariable("DB_PASSWORD");
    if (password.isEmpty()) {
        qCritical() << "Connexion impossible : DB_PASSWORD n'est pas configurée.";
        return false;
    }
    db.setPassword(password);
    if (db.open()) {
        qDebug() << "Connexion etablie";
        return true;
    }

    qDebug() << "Echec de la connexion :" << db.lastError().text();
    return false;
}
