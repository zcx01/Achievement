#include "AbstractFactoryClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AbstractFactoryClient w;
    w.Test();

    return a.exec();
}
