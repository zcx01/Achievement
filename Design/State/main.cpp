#include "StateClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StateClient w;
    w.Test();

    return a.exec();
}
