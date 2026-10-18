#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/logo.png"));

    MainWindow w;
    w.show();
    return a.exec();

    // Dans main.cpp par exemple
    if (!Connection::createInstance().createConnection()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de se connecter à la base de données. Vérifiez la source ODBC 'Projet' en 64 bits.");
        return -1; // On quitte l'application
    }
    // Ensuite seulement, on lance MainWindow
}
