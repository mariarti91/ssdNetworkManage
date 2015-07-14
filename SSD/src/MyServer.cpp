#include "MyServer.h"
#include <QMap>

MyServer::MyServer(QObject *parent) : QObject(parent), m_pNetworkManager(parent), m_pDataManager(parent)
{
    m_pUspdList = new QMap<quint8, QString>();
    connect(&m_pNetworkManager, SIGNAL(signalGetData(QByteArray)), &m_pDataManager, SLOT(slotDataHandler(QByteArray)));

    m_pUspdList = m_pDataManager.getUspdList();
    if(m_pUspdList->isEmpty())
    {
        qDebug() << "uspd list is empty!";
        return;
    }
    startTimer(10000);
}
//----------------------------------------------------------------------------

MyServer::~MyServer()
{
    m_pUspdList->clear();
    delete m_pUspdList;
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
