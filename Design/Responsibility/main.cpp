#include "ResponsibilityClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ResponsibilityClient w;
    w.Test();

    return a.exec();
}
