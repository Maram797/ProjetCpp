#pragma once

#include <QSqlDatabase>
#include <QString>

class Connection final {
public:
    static Connection &instance();
    static QString loadSavedPassword(QString *error = nullptr);
    static bool savePassword(const QString &password, QString *error = nullptr);
    void setPassword(const QString &password);
    bool open();
    QString lastError() const;

private:
    Connection();
    ~Connection();
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

    QSqlDatabase m_database;
    QString m_password;
    QString m_configurationError;
};
