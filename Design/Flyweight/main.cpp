#include "FlyweightClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlyweightClient w;
    w.Test();

    return a.exec();
}
