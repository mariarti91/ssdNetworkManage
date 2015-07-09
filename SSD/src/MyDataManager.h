#ifndef MYDATAMANAGER_H
#define MYDATAMANAGER_H

#include <QObject>

class MyDataManager : public QObject
{
    Q_OBJECT
public:
    explicit MyDataManager(QObject *parent = 0);

signals:

public slots:
    void slotDataHandler(QByteArray data);

};

#endif // MYDATAMANAGER_H
