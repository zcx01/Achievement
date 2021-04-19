#include "TemplateMethodClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TemplateMethodClient w;
    w.Test();

    return a.exec();
}
