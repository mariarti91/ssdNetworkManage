#include <QCoreApplication>

#include "MyServer.h"
#include "MyNetworkManager.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    MyServer server(&app);
    MyNetworkManager manager(&app);
    return app.exec();
}
