#include "MyServer.h"
#include <QMap>
#include <QDebug>

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    m_pDataBase = new MyDataBase();
    if(m_pDataBase->openDb("192.168.24.65", "VBD", "never", "123"))
        qDebug() << "connected to database";
    else
        qDebug() << "nope!";

    m_pUspdList = new QMap<quint8, QString>();
    if(m_pDataBase->executeQuery("SELECT id, network_address FROM uspd;"))
    {
        QSqlQuery query = m_pDataBase->lastSqlResult();

        while(query.next())
        {
            m_pUspdList->insert(query.value(0).toUInt(), query.value(1).toString());
        }
    }
    else
    {
        qDebug() << "sql query error";
    }
    connect(&m_pClient, SIGNAL(connected()), SLOT(slotClientConnected()));
    m_pClient.connectToHost();
}
//----------------------------------------------------------------------------

void MyServer::slotClientConnected()
{
    qDebug() << "client connected!!!";
    QAmqpQueue *output_queue = m_pClient.createQueue("uspd_list");
    connect(output_queue, SIGNAL(declared()), SLOT(slotOutputQueueDeclared()));
    output_queue->declare();
    QAmqpQueue *input_queue = m_pClient.createQueue("data");
    connect(input_queue, SIGNAL(declared()), SLOT(slotInputQueueDeclared()));
    input_queue->declare();
}
//----------------------------------------------------------------------------

void MyServer::slotOutputQueueDeclared()
{
    startTimer(5000);
}
//----------------------------------------------------------------------------

void MyServer::slotInputQueueDeclared()
{
    qDebug() << "input queue declared";
    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
    connect(queue, SIGNAL(messageReceived()), SLOT(slotMessageReceived()));
    queue->consume(QAmqpQueue::coNoAck);
    qDebug() << " [x] Server waiting for data";
}
//----------------------------------------------------------------------------

void MyServer::slotMessageReceived()
{
    qDebug() << " [x] Server have a new message:";
    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
    QAmqpMessage message = queue->dequeue();
    QByteArray data = QByteArray::fromBase64(message.payload());

    qDebug() << "DATA: " << data;

    quint8 uspd_id = data.data()[0];
    data.remove(0, 1);
    QString dt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << "uspd id: " << uspd_id << "\ndata: " << data << "\ndatetime: " << dt;
    if(!m_pDataBase->insertUspdReply(uspd_id, data, dt))
    {
        qDebug() << m_pDataBase->lastSqlResult().lastError();
    }
}
//----------------------------------------------------------------------------

MyServer::~MyServer()
{
    m_pUspdList->clear();
    delete m_pUspdList;
    m_pDataBase->closeDb();
    delete m_pDataBase;
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
