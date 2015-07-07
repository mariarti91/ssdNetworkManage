#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = 0);
    ~MySocket();

    void sendData(const QByteArray &data);

public slots:
    void slotStatusHandler(QAbstractSocket::SocketState state);
    void slotGetData();

private:
    quint16 m_pBlockSize;
    QTcpSocket* sock;
};

#endif // MYSOCKET_H
