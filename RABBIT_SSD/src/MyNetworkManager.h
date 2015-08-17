#ifndef MYNETWORKMANAGER_H
#define MYNETWORKMANAGER_H

#include <QObject>
#include "MySocket.h"

#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"

class MyNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkManager(QObject *parent = 0);
    ~MyNetworkManager();

    void sendData(const quint8& uspd_id, const QString &addr, const int &port, const QByteArray& data);

signals:
    void signalGetData(QByteArray data);
public slots:
    void slotGetDataHandler(QByteArray data);
    void slotClientConnected();
    void slotInputQueueDeclared();
    void slotOutputQueueDeclared();
    void slotMessageReceived();

private:
    QAmqpClient m_pClient;

};

#endif // MYNETWORKMANAGER_H
