#pragma once

#include <QSqlDatabase>

class Connection final {
public:
    static Connection &instance();
    bool open();
    QString lastError() const;

private:
    Connection();
    ~Connection();
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

    QSqlDatabase m_database;
};
