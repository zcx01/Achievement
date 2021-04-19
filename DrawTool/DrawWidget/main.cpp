#include "DrawWidgetFactory.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawWidgetFactory w;
    w.showMaximized();

    return a.exec();
}

