#include "gestionrendezvous.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    
    Connection &c = Connection::createInstance();
    const bool test = c.createConnection();

    if (!test) {
        QMessageBox::critical(
            nullptr,
            QObject::tr("Base de données"),
            QObject::tr("Échec de la connexion.\nVérifiez la source ODBC, "
                        "et configurez DB_PASSWORD dans les variables d'environnement."),
            QMessageBox::Cancel);
        return 1;
    }

    GestionRendezvous w;
    w.show();

    return a.exec();
}
