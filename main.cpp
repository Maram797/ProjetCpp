#include <QApplication>
#include <QMessageBox>
#include <QTextStream>

#include "connection.h"
#include "Petcarecenter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (app.arguments().contains("--test-connection")) {
        QTextStream out(stdout);
        if (Connection::createInstance().createConnection()) {
            out << "Oracle connection succeeded\n";
            return 0;
        }
        out << "Oracle connection failed: " << Connection::createInstance().lastError() << '\n';
        return 1;
    }

    Connection &connection = Connection::createInstance();
    if (!connection.createConnection()) {
        QMessageBox::critical(nullptr, QObject::tr("Base de données"),
                              QObject::tr("Connexion Oracle impossible.\n") + connection.lastError());
        return 1;
    }

    MainWindow w;
    w.show();
    QMessageBox::information(&w, QObject::tr("Base de données"), QObject::tr("Connexion Oracle réussie."));

    return app.exec();
}
