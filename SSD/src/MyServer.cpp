#include "MyServer.h"
#include <QMap>

MyServer::MyServer(QObject *parent) : QObject(parent), m_pNetworkManager(parent), m_pDataManager(parent)
{
    m_pUspdList = new QMap<quint8, QString>();
    connect(&m_pNetworkManager, SIGNAL(signalGetData(QByteArray)), &m_pDataManager, SLOT(slotDataHandler(QByteArray)));

    m_pDataBase = new MyDataBase();
    if(m_pDataBase->openDb("192.168.24.65", "VBD", "never", "123"))
        qDebug() << "connecting to database!!!";
    else
        qDebug() << "nope!";

    if(!getUspdList())
    {
        qDebug() << "getting uspdList error!";
        return;
    }
    startTimer(10000);
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
            m_pUspdList->insert(query.value(0).toUInt(), query.value(1).toString());
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

void MyServer::timerEvent(QTimerEvent *event)
{
    qDebug() << "\t uspd id\t\t address\t\t port";
    foreach (int key, m_pUspdList->keys())
    {
        QString addr = m_pUspdList->value(key);
        int port = QString(addr.split(':').at(1)).toUInt();
        addr = QString(addr.split(':').at(0));
        qDebug() << "\t" << key << "\t\t" << addr << "\t" << port;
        m_pNetworkManager.sendData(key, addr, port, QByteArray("1"));
    }
}
//----------------------------------------------------------------------------
