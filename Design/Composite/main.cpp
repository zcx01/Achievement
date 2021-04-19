#include "CompositeClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CompositeClient w;
    w.Test();

    return a.exec();
}
