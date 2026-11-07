#include <QApplication>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextStream>

#include "connection.h"
#include "Petcarecenter.h"

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
    bool passwordFromPrompt = false;
    bool passwordFromCredentialManager = false;
    if (password.isEmpty()) {
        QString credentialError;
        password = Connection::loadSavedPassword(&credentialError);
        passwordFromCredentialManager = !password.isEmpty();
        if (!credentialError.isEmpty()) {
            QMessageBox::warning(nullptr, QObject::tr("Gestionnaire d'identifiants"),
                                 QObject::tr("Impossible de lire le mot de passe enregistré.\n%1")
                                     .arg(credentialError));
        }
    }
    const auto promptForPassword = [&password, &passwordFromPrompt]() {
        bool ok = false;
        const QString enteredPassword = QInputDialog::getText(
            nullptr, QObject::tr("Connexion Oracle"),
            QObject::tr("Mot de passe Oracle pour %1")
                .arg(qEnvironmentVariable("PAWCHE_DB_USER", "PAWCHE_2")),
            QLineEdit::Password, QString(), &ok);
        if (!ok || enteredPassword.isEmpty())
            return false;
        password = enteredPassword;
        passwordFromPrompt = true;
        return true;
    };

    if (password.isEmpty() && !promptForPassword())
        return 0;

    Connection::instance().setPassword(password);
    bool connected = Connection::instance().open();
    if (!connected) {
        if (passwordFromCredentialManager) {
            QMessageBox::warning(nullptr, QObject::tr("Connexion Oracle"),
                                 QObject::tr("Le mot de passe enregistré a été refusé. Veuillez le saisir à nouveau."));
            if (!promptForPassword())
                return 0;
            Connection::instance().setPassword(password);
            connected = Connection::instance().open();
        }
    }

    if (!connected) {
        QMessageBox::critical(nullptr, QObject::tr("Base de données"),
                              QObject::tr("Connexion Oracle impossible.\n") + Connection::instance().lastError());
        return 1;
    }

    if (passwordFromPrompt) {
        QString credentialError;
        if (!Connection::savePassword(password, &credentialError)) {
            QMessageBox::warning(nullptr, QObject::tr("Gestionnaire d'identifiants"),
                                 QObject::tr("Impossible d'enregistrer le mot de passe dans le Gestionnaire d'identifiants Windows.\n%1")
                                     .arg(credentialError));
        }
    }

    MainWindow w;
    w.show();
    QMessageBox::information(&w, QObject::tr("Base de données"), QObject::tr("Connexion Oracle réussie."));

    return app.exec();
}
