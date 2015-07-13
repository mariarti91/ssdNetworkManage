#include "MyDataBase.h"

MyDataBase::MyDataBase() : m_bIsOpen(false)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_pQuery = new QSqlQuery(m_db);
}
//-------------------------------------------------------------------------

MyDataBase::~MyDataBase()
{
    if(m_bIsOpen) m_db.close();
    delete m_pQuery;
}
//-------------------------------------------------------------------------

bool MyDataBase::openDb(const QString &addr, const QString &dbname, const QString &login, const QString &pass)
{
    m_db.setHostName(addr);
    m_db.setPort(5432);
    m_db.setDatabaseName(dbname);
    m_db.setUserName(login);
    m_db.setPassword(pass);
    return m_db.open();
}
//------------------------------------------------------------------------

void MyDataBase::closeDb()
{
    if(m_bIsOpen) m_db.close();
}
//------------------------------------------------------------------------

bool MyDataBase::executeQuery(const QString &strQuery)
{
    if(m_pQuery->exec(strQuery))
        return true;
    else
    {
        qDebug() << m_pQuery->lastError();
        return false;
    }
}
//-------------------------------------------------------------------------

QSqlQuery MyDataBase::lastSqlResult()
{
    return *m_pQuery;
}
