#ifndef MYDATAMANAGER_H
#define MYDATAMANAGER_H

#include <QObject>

#include "MyDataBase.h"

class MyDataManager : public QObject
{
    Q_OBJECT
public:
    explicit MyDataManager(QObject *parent = 0);
    ~MyDataManager();

    QMap<quint8, QString>* getUspdList();
signals:

public slots:
    void slotDataHandler(QByteArray data);

private:
    MyDataBase *m_pDataBase;
};

#endif // MYDATAMANAGER_H
