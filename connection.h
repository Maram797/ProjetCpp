#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

/* Classe Connection (patron Singleton - Meyers Singleton)
 * Une seule connexion Oracle (via ODBC) pour toute l'application.
 * Acces : Connection::createInstance()
 * Ouverture : createConnection()
 */
class Connection
{
public:
    static Connection& createInstance();
    bool createConnection();

private:
    QSqlDatabase db;   // connexion persistante, stockee dans le Singleton

    Connection();      // constructeur prive : aucune creation depuis l'exterieur
    ~Connection();     // ferme proprement la connexion

    // Interdire la copie et l'affectation
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
};

#endif // CONNECTION_H
