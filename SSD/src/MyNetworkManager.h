#ifndef MYNETWORKMANAGER_H
#define MYNETWORKMANAGER_H

#include <QObject>
#include "MySocket.h"

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

private:
    QList<MySocket> *m_pConnections;
};

#endif // MYNETWORKMANAGER_H
