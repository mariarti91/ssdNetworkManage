#include "MyServer.h"
#include <QMap>
#include <QDebug>

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    m_pUspdList = new QMap<quint8, QString>();
    m_pUspdList->insert(1, QString("127.0.0.1:9191"));
    connect(&m_pClient, SIGNAL(connected()), SLOT(slotClientConnected()));
    m_pClient.connectToHost();
}
//----------------------------------------------------------------------------

void MyServer::slotClientConnected()
{
    qDebug() << "client connected!!!";
    QAmqpQueue *queue = m_pClient.createQueue("uspd_list");
    connect(queue, SIGNAL(declared()), SLOT(slotQueueDeclared()));
    queue->declare();
}
//----------------------------------------------------------------------------

void MyServer::slotQueueDeclared()
{
    startTimer(5000);
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
    QAmqpExchange *defaultExchange = m_pClient.createExchange();
    foreach (quint8 key, m_pUspdList->keys())
    {
        QString message = QString("%1:%2").arg(key).arg(m_pUspdList->value(key));
        defaultExchange->publish(message, "uspd_list");
        qDebug() << " [x] Sent " << message;

    }
}
//----------------------------------------------------------------------------
