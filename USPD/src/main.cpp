#include <QCoreApplication>

#include "MyServer.h"

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
    MyServer serv(&app);
    if(!serv.listen(QHostAddress::Any, 9191))
        qDebug() << "Server is not runned";
    else
        qDebug() << "server started";
	return app.exec();
}
