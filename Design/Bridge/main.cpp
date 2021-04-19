#include "BridgeClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BridgeClient w;
    w.Test();

    return a.exec();
}
