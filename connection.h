#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class Connection {
public:
    static Connection& createInstance(); // Méthode statique (Singleton)
    bool createConnection();             // Établir la connexion

private:
    QSqlDatabase db;
    Connection();                        // Constructeur privé
    ~Connection();                       // Destructeur privé
    Connection(const Connection&) = delete;            // Interdire la copie
    Connection& operator=(const Connection&) = delete; // Interdire l'affectation
};

#endif // CONNECTION_H