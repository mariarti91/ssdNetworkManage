#include "MyDataManager.h"

#include <QDebug>

MyDataManager::MyDataManager(QObject *parent) :
    QObject(parent)
{
    m_db = new SsdDataBase();
    if(m_db->openDb("192.168.24.65", "VBD", "never", "123"))
        qDebug() << "connecting to database!!!";
    else
        qDebug() << "nope!";
}
//----------------------------------------------------------------------

MyDataManager::~MyDataManager()
{
    delete m_db;
}
//----------------------------------------------------------------------

void MyDataManager::slotDataHandler(QByteArray data)
{
    qDebug() << "Data manager get data: " << data;
}
