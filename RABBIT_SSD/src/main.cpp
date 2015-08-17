#include <QCoreApplication>

#include "MyServer.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    MyServer serv(&app);
    return app.exec();
}
