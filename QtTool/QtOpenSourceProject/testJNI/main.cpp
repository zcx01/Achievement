#include "maininterface.h"

#include <QApplication>
#include"qdebug2logcat.h"

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("Mylog");
    QApplication a(argc, argv);
    MainInterface w;
    w.show();
    return a.exec();
}
