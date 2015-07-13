#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>

#include "MyNetworkManager.h"
#include "MyDataManager.h"
#include "MyDataBase.h"

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

    QMap<int, QString> *m_pUspdList;
};

#endif // MYSERVER_H
