#include "gestionrendezvous.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Instance unique du Singleton, puis tentative de connexion a Oracle
    Connection &c = Connection::createInstance();
    const bool test = c.createConnection();

    if (!test) {
        QMessageBox::critical(
            nullptr,
            QObject::tr("Base de données"),
            QObject::tr("Échec de la connexion.\nVérifiez la source ODBC, "
                        "l'utilisateur et le mot de passe dans connection.cpp."),
            QMessageBox::Cancel);
        return 1;
    }

    GestionRendezvous w;
    w.show();
    QMessageBox::information(
        &w,
        QObject::tr("Base de données"),
        QObject::tr("Connexion réussie."));

    return a.exec();
}
