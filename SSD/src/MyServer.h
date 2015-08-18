#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTimerEvent>

#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"

#include "MyDataBase.h"

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

signals:

public slots:
    void slotClientConnected();
    void slotOutputQueueDeclared();
    void slotInputQueueDeclared();
    void slotMessageReceived();

private:
    void timerEvent(QTimerEvent *event);

    QMap<quint8, QString> *m_pUspdList;
    QAmqpClient m_pClient;
    MyDataBase *m_pDataBase;

};

#endif // MYSERVER_H
