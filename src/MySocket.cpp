#include "MySocket.h"

#include <QDebug>
#include <QIODevice>

MySocket::MySocket(QObject *parent) : QTcpSocket(parent)
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
    this->write(data);
}
//---------------------------------------------------------------

void MySocket::slotGetData()
{
    QByteArray buf(this->readAll());
    qDebug() << QString(buf);
}
