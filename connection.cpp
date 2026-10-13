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

bool Connection::open()
{
    if (m_database.isOpen())
        return true;

    m_database.setDatabaseName(qEnvironmentVariable("PAWCHE_ODBC_DSN", "Source_Projet2A"));
    m_database.setUserName(qEnvironmentVariable("PAWCHE_DB_USER", "elyes"));
    // The environment variable takes priority.  The fallback keeps this
    // course project runnable directly from Qt Creator without extra setup.
    m_database.setPassword(qEnvironmentVariable("PAWCHE_DB_PASSWORD", "NewPass123"));
    return m_database.open();
}

QString Connection::lastError() const
{
    return m_database.lastError().text();
}
