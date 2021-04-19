#include <QApplication>
#include "StrategyClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StrategyClient s;
    s.Test();

    return a.exec();
}
