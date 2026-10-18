#include "connection.h"

#include <QSqlError>

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

void Connection::setPassword(const QString &password)
{
    m_password = password;
}

bool Connection::open()
{
    if (m_database.isOpen())
        return true;

    const QString dsn = qEnvironmentVariable("PAWCHE_ODBC_DSN", "Source_Projet2A");
    const QString user = qEnvironmentVariable("PAWCHE_DB_USER", "elyes");
    const QString password = m_password.isEmpty()
                                 ? qEnvironmentVariable("PAWCHE_DB_PASSWORD")
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
