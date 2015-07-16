#include "MyServer.h"

#include <QDebug>
#include <QTcpSocket>

#include "comands.h"

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
        if((quint16)client->bytesAvailable() < sizeof(quint16))
        {
            qDebug() << "malomalo";
            return;
        }
        stream >> m_pBlockSize;
        qDebug() << m_pBlockSize;
    }

    if((quint16)client->bytesAvailable() < m_pBlockSize) return;
    QByteArray buf;
    buf.resize(m_pBlockSize);
    stream >> buf;
    qDebug() << buf.toHex();
    m_pBlockSize = 0;

    //QByteArray buf;
    //buf = client->readAll();

    int comandId = buf.data()[0];
    qDebug() << comandId;
    switch (comandId)
    {
    case GET_ENERGY:
        sendData(QByteArray("\xff\x01\x04\x04\x60\x00\x00\x00\xf1\x8b", 10), *client);
        break;

    case GET_POWER:
        sendData(QByteArray("\xff\x01\x03\x04\x00\x00\x00\x00\xee\x3c", 10), *client);
        break;

    case GET_INFO:
        sendData(QByteArray("\xff\x01\x29\x05\xff\x03\x05\x0a\x1e\xb4\xa6", 11), *client);
        break;

    case GET_TRUE:
        sendData(QByteArray("\x00\x00\x00\x01\x01\xc9\x00\x00\x14\x00\x00\x00\x01\x01\xc9\x00\x14\x40\x00\x00\x00\x50\x00\x00\x00\x60\x00\x00\x00\x70\x00\x00\x00\x80\x00\x00\x00", 37), *client);
        break;

    default:
        sendData("\xff", *client);
        break;
    }
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
