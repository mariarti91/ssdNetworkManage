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
    void setUspdId(const quint8& id);

signals:
    void signalData(QByteArray);

public slots:
    void slotStatusHandler(QAbstractSocket::SocketState state);
    void slotGetData();

private:
    quint16 m_pBlockSize;
    QTcpSocket* sock;
    quint8 m_pUspdId;
};

#endif // MYSOCKET_H
