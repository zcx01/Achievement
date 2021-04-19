#include "InterperterClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterperterClient w;
    w.Test();

    return a.exec();
}
