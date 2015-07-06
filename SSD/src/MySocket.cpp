#include "MySocket.h"

#include <QDebug>
#include <QIODevice>

MySocket::MySocket(QObject *parent) : QTcpSocket(parent), m_pBlockSize(0)
{
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(slotStatusHandler(QAbstractSocket::SocketState)));
    connect(this, SIGNAL(readyRead()), SLOT(slotGetData()));
}
//---------------------------------------------------------------

MySocket::~MySocket()
{

}
//---------------------------------------------------------------

void MySocket::slotStatusHandler(QAbstractSocket::SocketState state)
{
    switch (state)
    {
    case QAbstractSocket::HostLookupState:
        qDebug() << "host lookup...";
        break;

    case QAbstractSocket::ConnectingState:
        qDebug() << "wait for connection...";
        if(!waitForConnected())
        {
            qDebug() << "ERROR: not connected";
        }
        break;

    case QAbstractSocket::ConnectedState:
        qDebug() << "connected!";
        break;

    case QAbstractSocket::UnconnectedState:
        qDebug() << "connectio terminate";
        this->deleteLater();
        break;

    default:
        qDebug() << state;
        break;
    }
}
//---------------------------------------------------------------

void MySocket::sendData(const QByteArray &data)
{
    qDebug() << "sending data...";

    if(this->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "ERROR: connecting error";
        return;
    }

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);

    sendStream << quint16(0) << data;
    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));

    this->write(block);
    if(this->waitForBytesWritten())
        qDebug() << "complite.";
    else
        qDebug() << "ERROD: data not sended";
}
//---------------------------------------------------------------

void MySocket::slotGetData()
{
    qDebug() << "get data!";
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
