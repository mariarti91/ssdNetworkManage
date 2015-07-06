#include <QCoreApplication>
#include <QDebug>

#include "MySocket.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
    MySocket *sock = new MySocket(&app);
    sock->connectToHost("127.0.0.1", 9191, QTcpSocket::ReadWrite);
    sock->sendData("Hello!");
	return app.exec();
}
