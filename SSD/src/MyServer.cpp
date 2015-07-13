#include "MyServer.h"
#include <QMap>

MyServer::MyServer(QObject *parent) : QObject(parent), m_pNetworkManager(parent), m_pDataManager(parent)
{
    m_pUspdList = new QMap<int, QString>;
    connect(&m_pNetworkManager, SIGNAL(signalGetData(QByteArray)), &m_pDataManager, SLOT(slotDataHandler(QByteArray)));
    m_pNetworkManager.sendData("127.0.0.1", 9191, "ololo");

    m_pDataBase = new MyDataBase();
    if(m_pDataBase->openDb("192.168.24.65", "VBD", "never", "123"))
        qDebug() << "connecting to database!!!";
    else
        qDebug() << "nope!";
}
//----------------------------------------------------------------------------

MyServer::~MyServer()
{
    m_pDataBase->closeDb();
    delete m_pDataBase;
}
//----------------------------------------------------------------------------

bool MyServer::getUspdList()
{
    return 0;
}
//----------------------------------------------------------------------------
