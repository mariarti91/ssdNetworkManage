#include "MySocket.h"

#include <QDebug>
#include <QIODevice>

MySocket::MySocket(QObject *parent) : QTcpSocket(parent), m_pBlockSize(0)
{
    connect(this, SIGNAL(readyRead()), SLOT(slotGetData()));
}
//---------------------------------------------------------------

MySocket::~MySocket()
{

}
//---------------------------------------------------------------

void MySocket::sendData(const QByteArray &data)
{

    if(this->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "wait for connection...";
        if(!this->waitForConnected())
        {
            qDebug() << "Fail. connecting error.";
            return;
        }
        else
            qDebug() << "connected.";
    }

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);

    sendStream << quint16(0) << data;
    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));

    qDebug() << "sending data...";
    this->write(block);
    if(this->waitForBytesWritten())
        qDebug() << "complite.";
    else
        qDebug() << "ERROD: data not sended";
}
//---------------------------------------------------------------

void MySocket::slotGetData()
{
    qDebug() << "getting data...";
    QDataStream stream(this);

    if(!m_pBlockSize)
    {
        if((quint16)this->bytesAvailable() < sizeof(quint16)) return;
        stream >> m_pBlockSize;
    }

    if((quint16)this->bytesAvailable() < m_pBlockSize) return;
    QByteArray buf;
    buf.resize(m_pBlockSize);
    stream >> buf;
    m_pBlockSize = 0;
    qDebug() << buf;
}
