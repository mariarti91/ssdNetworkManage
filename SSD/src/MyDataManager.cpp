#include "MyDataManager.h"

#include <QDebug>

MyDataManager::MyDataManager(QObject *parent) :
    QObject(parent)
{

}
//----------------------------------------------------------------------

MyDataManager::~MyDataManager()
{
}
//----------------------------------------------------------------------

void MyDataManager::slotDataHandler(QByteArray data)
{
    qDebug() << "Data manager geted data:";

    quint8 uspd_id = data.data()[0];
    data.remove(0, 1);

    qDebug() << "uspd id: " << uspd_id << "data: " << data;
}
