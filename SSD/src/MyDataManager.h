#ifndef MYDATAMANAGER_H
#define MYDATAMANAGER_H

#include <QObject>

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

};

#endif // MYDATAMANAGER_H
