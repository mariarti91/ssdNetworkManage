#include "SsdDataBase.h"

SsdDataBase::SsdDataBase() : m_bIsOpen(false)
{
    m_db = new QSqlDatabase();
    m_db->addDatabase("QPSQL");
}
//-------------------------------------------------------------------------

SsdDataBase::~SsdDataBase()
{
    if(m_bIsOpen) m_db->close();
    delete m_db;
}
//-------------------------------------------------------------------------

bool SsdDataBase::openDb(const QString &addr, const QString &dbname, const QString &login, const QString &pass)
{
    m_db->setHostName(addr);
    m_db->setPort(5432);
    m_db->setDatabaseName(dbname);
    m_db->setUserName(login);
    m_db->setPassword(pass);
    m_db->open();
    qDebug() << m_db->lastError();
    qDebug() << QSqlDatabase::drivers();
    //return m_db->open();
}
//------------------------------------------------------------------------

void SsdDataBase::closeDb()
{
    if(m_bIsOpen) m_db->close();
}
