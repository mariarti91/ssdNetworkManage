#ifndef MYDATAMANAGER_H
#define MYDATAMANAGER_H

#include <QObject>

#include "SsdDataBase.h"

class MyDataManager : public QObject
{
    Q_OBJECT
public:
    explicit MyDataManager(QObject *parent = 0);
    ~MyDataManager();
signals:

public slots:
    void slotDataHandler(QByteArray data);

private:
    SsdDataBase *m_db;

};

#endif // MYDATAMANAGER_H
