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

    bool executeQuery(const QString& strQuery);
    QSqlQuery lastSqlResult();

private:
    QSqlDatabase m_db;
    bool m_bIsOpen;
    QSqlQuery* m_pQuery;
};

#endif // SSDDATABASE_H
