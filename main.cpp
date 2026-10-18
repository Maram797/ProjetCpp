#include <QApplication>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextStream>

#include "connection.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (app.arguments().contains("--test-connection")) {
        QTextStream out(stdout);
        if (Connection::instance().open()) {
            out << "Oracle connection succeeded\n";
            return 0;
        }
        out << "Oracle connection failed: " << Connection::instance().lastError() << '\n';
        return 1;
    }

    QString password = qEnvironmentVariable("PAWCHE_DB_PASSWORD");
    if (password.isEmpty()) {
        bool ok = false;
        password = QInputDialog::getText(
            nullptr, QObject::tr("Connexion Oracle"),
            QObject::tr("Mot de passe Oracle pour %1")
                .arg(qEnvironmentVariable("PAWCHE_DB_USER", "elyes")),
            QLineEdit::Password, QString(), &ok);
        if (!ok || password.isEmpty())
            return 0;
    }
    Connection::instance().setPassword(password);

    if (!Connection::instance().open()) {
        QMessageBox::critical(nullptr, QObject::tr("Base de données"),
                              QObject::tr("Connexion Oracle impossible.\n") + Connection::instance().lastError());
        return 1;
    }

    MainWindow w;
    w.show();
    QMessageBox::information(&w, QObject::tr("Base de données"), QObject::tr("Connexion Oracle réussie."));

    return app.exec();
}
