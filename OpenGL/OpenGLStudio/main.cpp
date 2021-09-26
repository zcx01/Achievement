#include "MainNavigationWidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString qssFileName =":/config/qss/MainNavigationWidget.qss";
    QFile qssFile(qssFileName);
    if(qssFile.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(qssFile.readAll());
    }

    MainNavigationWidget window;
    window.resize(640, 480);
    window.show();


    return a.exec();
}
