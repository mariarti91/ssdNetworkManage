#include "MyDataManager.h"

#include <QDebug>

MyDataManager::MyDataManager(QObject *parent) :
    QObject(parent)
{
}
//----------------------------------------------------------------------

void MyDataManager::slotDataHandler(QByteArray data)
{
    qDebug() << "Data manager get data: " << data;
}
