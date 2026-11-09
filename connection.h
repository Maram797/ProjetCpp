#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QString>

class Connection final {
public:
    static Connection &createInstance();
    bool createConnection();
    QString lastError() const;

private:
    Connection();
    ~Connection();
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

    QSqlDatabase db;
};

#endif // CONNECTION_H
