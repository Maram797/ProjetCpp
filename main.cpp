#include "petcarecenter.h" // Modifié ici
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/logo.png"));

    if (!Connection::createInstance().createConnection()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
        return -1;
    }

    Petcarecenter w; // Modifié ici
    w.show();

    return a.exec();
}