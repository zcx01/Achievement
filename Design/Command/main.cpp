#include "CommandClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommandClient w;
    w.Test();

    return a.exec();
}
