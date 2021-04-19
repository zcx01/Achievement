#include "PrototypeClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrototypeClient w;
    w.Test();

    return a.exec();
}
