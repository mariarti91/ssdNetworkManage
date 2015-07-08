#include "MyNetworkManager.h"

#include <QList>

MyNetworkManager::MyNetworkManager(QObject *parent) :
    QObject(parent)
{
    m_pConnections = new QList<MySocket>();
}
//-------------------------------------------------------------------------------------

MyNetworkManager::~MyNetworkManager()
{
    //TODO
    delete m_pConnections;
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::sendData(const QString &addr, const int &port, const QByteArray& data)
{
    MySocket *sock = new MySocket(this);
    sock->connectToHost(addr, port, QTcpSocket::ReadWrite);
    connect(sock, SIGNAL(signalData(QByteArray)), SIGNAL(signalGetData(QByteArray)));
    sock->sendData(data);
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::slotGetDataHandler(QByteArray data)
{
    qDebug() << "Have a new data";
    qDebug() << data;
}
//-------------------------------------------------------------------------------------
