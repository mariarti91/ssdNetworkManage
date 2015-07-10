#include <QCoreApplication>
#include <QDebug>

#include "MyNetworkManager.h"
#include "MyDataManager.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
    MyDataManager dm(&app);
    MyNetworkManager nm(&app);
    QObject::connect(&nm, SIGNAL(signalGetData(QByteArray)), &dm, SLOT(slotDataHandler(QByteArray)));
    nm.sendData("127.0.0.1", 9191, "ololo");

	return app.exec();
}
