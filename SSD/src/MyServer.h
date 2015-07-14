#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>

#include "MyNetworkManager.h"
#include "MyDataManager.h"
#include "MyDataBase.h"

#include <QTimerEvent>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

signals:

public slots:

private:
    bool getUspdList();

    MyNetworkManager m_pNetworkManager;
    MyDataManager m_pDataManager;
    MyDataBase *m_pDataBase;

    void timerEvent(QTimerEvent *event);

    QMap<quint8, QString> *m_pUspdList;
};

#endif // MYSERVER_H
