#include <QCoreApplication>
#include <QDebug>

#include "MyNetworkManager.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
    MyNetworkManager nm(&app);
    nm.sendData("127.0.0.1", 9191, "ololo");
	return app.exec();
}
