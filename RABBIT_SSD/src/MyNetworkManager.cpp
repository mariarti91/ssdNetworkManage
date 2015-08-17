#include "MyNetworkManager.h"

#include <QList>

MyNetworkManager::MyNetworkManager(QObject *parent) :
    QObject(parent)
{
    connect(&m_pClient, SIGNAL(connected()), SLOT(slotClientConnected()));
    connect(this, SIGNAL(signalGetData(QByteArray)), SLOT(slotGetDataHandler(QByteArray)));
    m_pClient.connectToHost();
}
//-------------------------------------------------------------------------------------

MyNetworkManager::~MyNetworkManager()
{

}
//-------------------------------------------------------------------------------------

void MyNetworkManager::slotClientConnected()
{
    qDebug() << "client connected!!!";
    QAmqpQueue *input_queue = m_pClient.createQueue("uspd_list");
    QAmqpQueue *output_queue = m_pClient.createQueue("data");
    connect(input_queue, SIGNAL(declared()), SLOT(slotInputQueueDeclared()));
    connect(output_queue, SIGNAL(declared()), SLOT(slotOutputQueueDeclared()));
    input_queue->declare();
    output_queue->declare();
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::slotInputQueueDeclared()
{
    qDebug() << "Input queue declared";
    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
    if(!queue)
    {
        qDebug() << "queue us empty";
        return;
    }
    connect(queue, SIGNAL(messageReceived()), SLOT(slotMessageReceived()));
    queue->consume(QAmqpQueue::coNoAck);
    qDebug() << " [*] Waiting for message from uspd_list queue";
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::slotMessageReceived()
{
    qDebug() << " [x] Have a new message:";
    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
    QAmqpMessage message = queue->dequeue();
    QStringList buf = QString(message.payload()).split(':');
    quint8 uspd_id = QString(buf.at(0)).toUInt();
    QString addr = buf.at(1);
    int port = QString(buf.at(2)).toInt();
    sendData(uspd_id, addr, port, QByteArray("4"));
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::slotOutputQueueDeclared()
{
    qDebug() << "output queue declared";
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::sendData(const quint8 &uspd_id, const QString &addr, const int &port, const QByteArray& data)
{
    MySocket *sock = new MySocket(this);
    sock->setUspdId(uspd_id);
    sock->connectToHost(addr, port, QTcpSocket::ReadWrite);
    connect(sock, SIGNAL(signalData(QByteArray)), SIGNAL(signalGetData(QByteArray)));
    sock->sendData(data);
}
//-------------------------------------------------------------------------------------

void MyNetworkManager::slotGetDataHandler(QByteArray data)
{
    QAmqpExchange *defaultExchange = m_pClient.createExchange();
    defaultExchange->publish(data, "data");
    qDebug() << " [x] Sent " << data;
}
//-------------------------------------------------------------------------------------
