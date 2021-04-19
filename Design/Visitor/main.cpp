#include "VisitorClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisitorClient w;
    w.Test();

    return a.exec();
}
