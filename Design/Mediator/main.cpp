#include "MediatorClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MediatorClient w;
    w.Test();

    return a.exec();
}
