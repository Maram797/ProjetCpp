#include "connection.h"

#include <QByteArray>
#include <QSqlError>

#include <windows.h>
#include <wincred.h>

namespace {
QString credentialTarget()
{
    const QString user = qEnvironmentVariable("PAWCHE_DB_USER", "PAWCHE_2");
    const QString dsn = qEnvironmentVariable("PAWCHE_ODBC_DSN", "Source_Projet2A");
    return QStringLiteral("Pawche/Oracle/%1/%2").arg(user, dsn);
}
}

Connection::Connection()
    : m_database(QSqlDatabase::addDatabase("QODBC"))
{
}

Connection::~Connection()
{
    if (m_database.isOpen())
        m_database.close();
}

Connection &Connection::instance()
{
    static Connection connection;
    return connection;
}

QString Connection::loadSavedPassword(QString *error)
{
    if (error)
        error->clear();

    PCREDENTIALW credential = nullptr;
    const QString target = credentialTarget();
    if (!CredReadW(reinterpret_cast<LPCWSTR>(target.utf16()), CRED_TYPE_GENERIC, 0, &credential)) {
        const DWORD code = GetLastError();
        if (code != ERROR_NOT_FOUND && error)
            *error = QStringLiteral("Windows Credential Manager error %1.").arg(code);
        return {};
    }

    const QString password = QString::fromUtf8(
        reinterpret_cast<const char *>(credential->CredentialBlob),
        static_cast<int>(credential->CredentialBlobSize));
    CredFree(credential);
    return password;
}

bool Connection::savePassword(const QString &password, QString *error)
{
    if (error)
        error->clear();

    const QByteArray passwordBytes = password.toUtf8();
    const QString target = credentialTarget();
    const QString user = qEnvironmentVariable("PAWCHE_DB_USER", "PAWCHE_2");
    CREDENTIALW credential = {};
    credential.Type = CRED_TYPE_GENERIC;
    credential.TargetName = const_cast<LPWSTR>(reinterpret_cast<LPCWSTR>(target.utf16()));
    credential.CredentialBlobSize = static_cast<DWORD>(passwordBytes.size());
    credential.CredentialBlob = reinterpret_cast<LPBYTE>(const_cast<char *>(passwordBytes.constData()));
    credential.Persist = CRED_PERSIST_LOCAL_MACHINE;
    credential.UserName = const_cast<LPWSTR>(reinterpret_cast<LPCWSTR>(user.utf16()));

    if (CredWriteW(&credential, 0))
        return true;

    if (error)
        *error = QStringLiteral("Windows Credential Manager error %1.").arg(GetLastError());
    return false;
}

void Connection::setPassword(const QString &password)
{
    m_password = password;
}

bool Connection::open()
{
    if (m_database.isOpen())
        return true;

    const QString dsn = qEnvironmentVariable("PAWCHE_ODBC_DSN", "Source_Projet2A");
    const QString user = qEnvironmentVariable("PAWCHE_DB_USER", "PAWCHE_2");
    const QString password = m_password.isEmpty()
                                 ? qEnvironmentVariable("PAWCHE_DB_PASSWORD", "1234")
                                 : m_password;

    if (password.isEmpty()) {
        m_configurationError = QStringLiteral("Oracle password is required.");
        return false;
    }

    m_configurationError.clear();
    m_database.setDatabaseName(dsn);
    m_database.setUserName(user);
    m_database.setPassword(password);
    return m_database.open();
}

QString Connection::lastError() const
{
    return m_configurationError.isEmpty() ? m_database.lastError().text() : m_configurationError;
}
