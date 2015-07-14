#include "MyDataManager.h"

#include <QDebug>

MyDataManager::MyDataManager(QObject *parent) :
    QObject(parent)
{
    m_pDataBase = new MyDataBase();
    if(m_pDataBase->openDb("192.168.24.65", "VBD", "never", "123"))
        qDebug() << "connected to database!!!";
    else
        qDebug() << "nope!";
}
//----------------------------------------------------------------------

MyDataManager::~MyDataManager()
{
    m_pDataBase->closeDb();
    delete m_pDataBase;
}
//----------------------------------------------------------------------

void MyDataManager::slotDataHandler(QByteArray data)
{
    qDebug() << "Data manager geted data:";

    quint8 uspd_id = data.data()[0];
    data.remove(0, 1);

    qDebug() << "uspd id: " << uspd_id << "data: " << data;
    if(!m_pDataBase->insertUspdReply(uspd_id, data))
    {
        qDebug() << m_pDataBase->lastSqlResult().lastError();
    }
}
//----------------------------------------------------------------------

QMap<quint8, QString> *MyDataManager::getUspdList()
{
    QMap<quint8, QString>* list = new QMap<quint8, QString>();
    if(m_pDataBase->executeQuery("SELECT id, network_address FROM uspd;"))
    {
        QSqlQuery query = m_pDataBase->lastSqlResult();

        while(query.next())
        {
            list->insert(query.value(0).toUInt(), query.value(1).toString());
        }

        /*qDebug() << "id\t address";
        foreach (int key, m_pUspdList->keys())
        {
            qDebug() << key << "\t" << m_pUspdList->value(key);
        }*/
    }
    else
    {
        qDebug() << "sql query error";
    }
    return list;
}
//-----------------------------------------------------------------------
