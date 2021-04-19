#include "CGraphicsView.h"
#include <QApplication>
#include "CZDrawManagement.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CZDrawManagement managment;

    QString tmp = "leida";
    QString fileName = QApplication::applicationDirPath()+QString("/config/%1/").arg(tmp);
    QString toolFileName = fileName+"ToolConfig.xml";
    qDebug()<<toolFileName;
    managment.loadTool(toolFileName);

    QString itemToolFileName = fileName+"ItemToolConfig.xml";
    qDebug()<<itemToolFileName;
    managment.configItemTool(itemToolFileName);

    QString itemFileName = fileName+"ItemConfig.xml";
    qDebug()<<itemFileName;
    managment.loadItemFileName(itemFileName);

    managment.setVisible(true);


    //切换背景图片
    //    ItemAttrPtr ptr =managment.getItemAttr("background");//background为背景图片的Id
    //    ptr->attrs.insert(CURRENTINDEX,"1");//更新为第二张背景图
    //    managment.upDateItemAttr(ptr);
    CZDrawManagement managment1;
    //#ifdef leida
    //    QString tmp = "leida";
    //#else
    tmp = "adsorb";
    //#endif
    fileName = QApplication::applicationDirPath()+QString("/config/%1/").arg(tmp);
    toolFileName = fileName+"ToolConfig.xml";
    qDebug()<<toolFileName;
    managment1.loadTool(toolFileName);

    itemToolFileName = fileName+"ItemToolConfig.xml";
    qDebug()<<itemToolFileName;
    managment1.configItemTool(itemToolFileName);

    itemFileName = fileName+"ItemConfig.xml";
    qDebug()<<itemFileName;
    managment1.loadItemFileName(itemFileName);

    managment1.setVisible(true);
    return a.exec();
}
