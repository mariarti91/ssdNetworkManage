#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

    void sendData(const QByteArray &data, QTcpSocket &sock);

public slots:
    void slotNewConnectionHandler();
    void slotGetData();

private:
    quint16 m_pBlockSize;
};

#endif // MYSERVER_H
