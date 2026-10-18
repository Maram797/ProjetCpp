#include "connection.h"
#include <QMessageBox>
#include <QDebug>

Connection::Connection() {
    // On utilise le pilote ODBC
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection() {
    if (db.isOpen()) {
        db.close();
    }
}

Connection& Connection::createInstance() {
    static Connection instance;
    return instance;
}

bool Connection::createConnection() {
    // Assurez-vous que le nom correspond EXACTEMENT à celui dans ODBC 64 bits
    db.setDatabaseName("Projet");
    db.setUserName("system");
    db.setPassword("nff14468000");

    if (db.open()) {
        qDebug() << "Connexion à Oracle réussie !";
        return true;
    } else {
        // Affiche l'erreur précise (IM002, ORA-12170, etc.)
        qDebug() << "ÉCHEC DE LA CONNEXION ODBC :" << db.lastError().text();
        return false;
    }
}