#include "MyServer.h"

#include <QDebug>
#include <QTcpSocket>

MyServer::MyServer(QObject *parent) : QTcpServer(parent), m_pBlockSize(0)
{
    connect(this, SIGNAL(newConnection()), SLOT(slotNewConnectionHandler()));
}
//---------------------------------------------------------------------------

MyServer::~MyServer(){}
//---------------------------------------------------------------------------

void MyServer::slotNewConnectionHandler()
{
    qDebug() << "geted new connection";
    QTcpSocket* sock = this->nextPendingConnection();
    connect(sock, SIGNAL(readyRead()), this, SLOT(slotGetData()));
}
//---------------------------------------------------------------------------

void MyServer::slotGetData()
{
    qDebug() << "getting data...";

    QTcpSocket *client = (QTcpSocket*)sender();
    QDataStream stream(client);

    if(!m_pBlockSize)
    {
        if((quint16)client->bytesAvailable() < sizeof(quint16)) return;
        stream >> m_pBlockSize;
    }

    if((quint16)client->bytesAvailable() < m_pBlockSize) return;
    QByteArray buf;
    buf.resize(m_pBlockSize);
    stream >> buf;
    m_pBlockSize = 0;
    qDebug() << buf;

    sendData("Hello!", *client);
}
//-------------------------------------------------------------------------

void MyServer::sendData(const QByteArray &data, QTcpSocket &sock)
{
    qDebug() << "sending data...";

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);

    sendStream << quint16(0) << data;
    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));

    sock.write(block);
    if(sock.waitForBytesWritten())
        qDebug() << "complite.";
    else
        qDebug() << "ERROR: data not sended";
}
//-------------------------------------------------------------------------
