#include "FlowChartWindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *pGbkCodec = QTextCodec::codecForName("GBK");

    if (pGbkCodec == 0)
    {
        pGbkCodec = QTextCodec::codecForLocale();
    }
    QTextCodec::setCodecForLocale(pGbkCodec);

#if QT_VERSION >= 0x050000

#else
    QTextCodec::setCodecForCStrings(pGbkCodec);
    QTextCodec::setCodecForTr(pGbkCodec);
#endif
    FlowChartWindow w;
    w.showMaximized();


//    MainWindow w1;
//    w1.showMaximized();
    return a.exec();
}
