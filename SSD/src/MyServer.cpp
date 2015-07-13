#include "MyServer.h"
#include <QMap>

MyServer::MyServer(QObject *parent) : QObject(parent), m_pNetworkManager(parent), m_pDataManager(parent)
{
    m_pUspdList = new QMap<int, QString>();
    connect(&m_pNetworkManager, SIGNAL(signalGetData(QByteArray)), &m_pDataManager, SLOT(slotDataHandler(QByteArray)));
    //m_pNetworkManager.sendData("127.0.0.1", 9191, "ololo");

    m_pDataBase = new MyDataBase();
    if(m_pDataBase->openDb("192.168.24.65", "VBD", "never", "123"))
        qDebug() << "connecting to database!!!";
    else
        qDebug() << "nope!";

    getUspdList();
}
//----------------------------------------------------------------------------

MyServer::~MyServer()
{
    m_pDataBase->closeDb();
    delete m_pDataBase;
    m_pUspdList->clear();
    delete m_pUspdList;
}
//----------------------------------------------------------------------------

bool MyServer::getUspdList()
{
    if(m_pDataBase->executeQuery("SELECT id, network_address FROM uspd;"))
    {
        QSqlQuery query = m_pDataBase->lastSqlResult();

        while(query.next())
        {
            m_pUspdList->insert(query.value(0).toInt(), query.value(1).toString());
        }

        /*qDebug() << "id\t address";
        foreach (int key, m_pUspdList->keys())
        {
            qDebug() << key << "\t" << m_pUspdList->value(key);
        }*/
        return true;
    }
    {
        qDebug() << "sql query error";
        return false;
    }
}
//----------------------------------------------------------------------------
