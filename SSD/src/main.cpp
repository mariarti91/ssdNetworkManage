#include <QCoreApplication>
#include <QDebug>

#include "MyServer.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    MyServer server(&app);
	return app.exec();
}
