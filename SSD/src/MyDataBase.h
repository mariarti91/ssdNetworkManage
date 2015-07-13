#ifndef SSDDATABASE_H
#define SSDDATABASE_H

#include <QSqlDatabase>
#include <QtSql>

class MyDataBase
{
public:
    MyDataBase();
    ~MyDataBase();

    bool openDb(const QString& addr, const QString& dbname, const QString& login, const QString& pass);
    void closeDb();

private:
    QSqlDatabase m_db;
    bool m_bIsOpen;
};

#endif // SSDDATABASE_H
