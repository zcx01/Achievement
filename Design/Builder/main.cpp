#include "BuilderClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BuilderClient w;
    w.Test();

    return a.exec();
}
