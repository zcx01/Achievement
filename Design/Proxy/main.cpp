#include "ProxyClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProxyClient w;
    w.Test();
    return a.exec();
}
