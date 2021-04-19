#include "AdapterClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdapterClient w;
    w.Test();

    return a.exec();
}
