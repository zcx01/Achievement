#include "FlowChartWindow.h"
#include "ui_MainWindow.h"
#include "ZPFun/GuiHanle.h"
//#include "./BaseDraw/CManagement.h"
#include <QDebug>
#include <QHBoxLayout>
#include "CDragButton.h"
#include <QLibrary>
#include "PropertyWidget/PropertyWidget/PropertyWidget.h"
#include "CButtonGroup/CButtonGroup.h"
#include "../BaseDraw/CManagement.h"
#include <QTime>
#include "../DrawToolInclude/commdefine.h"
#include "../DrawToolInclude/itemtooldefine.h"
#include "../DrawToolInclude/zattrdefine.h"

FlowChartWindow::FlowChartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load("ItemTool");
    load("ItemDraw");
    load("ExpanSingProperty");

    QString tmp = "FlowChart";
    QString fileName = QApplication::applicationDirPath()+QString("/config/%1/").arg(tmp);

    m_NewBulidItemBtn = new CButtonGroup;
    QString btnFileName = fileName+"UI/NewBulidItemBtn.xml";
    QString btnQssFileName = fileName+"qss/NewBulidItemBtn.qss";
    m_NewBulidItemBtn->loadConfigFile(btnFileName);
    m_NewBulidItemBtn->setUiStyle(btnQssFileName);

    //初始化图元
    m_Managment = new CManagement;
    m_ToolFileName = fileName+"ToolConfig.xml";
    m_Managment->loadTool(m_ToolFileName);

    m_ItemToolFileName = fileName+"ItemToolConfig.xml";
    m_Managment->configItemTool(m_ItemToolFileName);

    QString itemFileName = fileName+"ItemConfig.xml";
    m_Managment->loadItemFileName(itemFileName);


    m_Button = new CDragButton;
    //m_MianLyout->addWidget(m_Button);

    //添加属性窗体
    m_PropertyWidget = new PropertyWidget();

    connect(m_Button,SIGNAL(sig_Drag()),this,SLOT(slot_Drag()));
    connect(m_Managment,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_AttrChanged(QString,QString)));
    connect(m_Managment,SIGNAL(sig_CurrentChanged(QString,QString)),this,SLOT(slot_CurrentChanged(QString,QString)));
    //slot_Edit();

    //创建菜单
    createMenu();


    //添加图元窗体
    m_MianLyout= new QHBoxLayout(this->centralWidget());
    m_MianLyout->setMargin(0);

    //加入布局
    QVBoxLayout *btnLayout = new QVBoxLayout;
    btnLayout->addWidget(m_NewBulidItemBtn);
    btnLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    m_MianLyout->addLayout(btnLayout);
    m_MianLyout->addWidget(m_Managment->getWidget());
    m_MianLyout->addWidget(m_PropertyWidget);
    m_MianLyout->setStretchFactor(btnLayout,1);
    m_MianLyout->setStretchFactor(m_Managment->getWidget(),16);
    m_MianLyout->setStretchFactor(m_PropertyWidget,3);
    //连接信号与槽
    connect(m_NewBulidItemBtn,SIGNAL(sig_ButtonClick(QString)),this,SLOT(slot_NewItem(QString)));

    qDebug()<<(int)(QGraphicsItem::ItemIsFocusable|2049|QGraphicsItem::ItemIsSelectable);

    //    QVariantMap attrs =m_Managment->getAttrByItemType("DrawRect");
    //    attrs.remove("Id");
    //    QTime time;
    //    time.start();
    //    for(int i =0; i < 50000; i++)
    //    {
    //        m_Managment->createItem("DrawRect",attrs);
    //    }
    //    qDebug()<<(double)time.elapsed()/1000<<"Dsssssssdd";
}

FlowChartWindow::~FlowChartWindow()
{
    delete ui;

}

void FlowChartWindow::slot_Test()
{

}

void FlowChartWindow::slot_NewItem(QString type)
{
    slot_EditEnd();
    QString id = m_Managment->createItemByType(type);
    if(id.isEmpty()) return;
    m_Managment->setCurrentId(id);
    m_Managment->setEdit(CZDRAW::NewBulid);
}

void FlowChartWindow::slot_Edit()
{
    m_Managment->setEdit(CZDRAW::Edit);
}

void FlowChartWindow::slot_EditEnd()
{
    m_Managment->setEdit(CZDRAW::NoEdit);
    m_Managment->upDateTool("DisPlayName",m_Managment->getCurrentId());
}

void FlowChartWindow::slot_EditFold()
{
    QVariantMap attrs;
    attrs.insert(SCALE,1);
    attrs.insert(PENS,"0|255,0,0,255|1");
    attrs.insert(FOLDARROWSSTYLE,"SealTriangle");
    attrs.insert(FOLDNODEBRUSH,"255,255,0,255|1");
    attrs.insert(FOLDANODESTYLE,"1");
    QString id = m_Managment->createItem("FoldLine",attrs);
    m_Managment->setCurrentId(id);
    m_Managment->setEdit(CZDRAW::Edit);
}

void FlowChartWindow::slot_InsterPoint()
{
    handFoldLine(Dr::Insert);
}

void FlowChartWindow::slot_DeletePoint()
{
    handFoldLine(Dr::Delete);
}

void FlowChartWindow::slot_SetZValue()
{
    m_Managment->upDateToolData(m_Managment->getCurrentId(),"ColldingZValue",NULL).toInt();
}

void FlowChartWindow::slot_Delete()
{
    m_Managment->deleteItem(m_Managment->getCurrentId());
}

void FlowChartWindow::slot_Save()
{
    QString fileName = "C:/Users/lenovo/Desktop/ItemConfig.xml";
    m_Managment->saveItemFile(fileName);
    m_Managment->saveTool(m_ToolFileName);
    m_Managment->saveConfigItemTool(m_ItemToolFileName);
}

void FlowChartWindow::slot_HorizontalAlignment()
{
    AlignmentType("HorizontalAlignment|HorizontalEquidistant|Center");
}

void FlowChartWindow::slot_VerticalAlignment()
{
    AlignmentType("VerticalAlignment|VerticalEquidistant|Center");
}

void FlowChartWindow::slot_AttrChanged(QString id,QString attr)
{
    if(attr == BOUNDRECT && m_Managment->getEdit() == CZDRAW::NoEdit)
    {
        m_Managment->upDateTool("DisPlayName",id);
    }
    //  qDebug()<<m_Managment->getViewAttr();
}

void FlowChartWindow::slot_Drag()
{
    QVariantMap attrs = m_Managment->getItemAttr("00001")->attrs;
    attrs.insert(ID,"00dsf");
    m_Managment->createItem("CDrawImage",attrs);
    //m_Managment->upDateClassTool("CDrawImage",attrs.value(ID).toString());
    //m_Button->setDropData(m_Managment->getAttrByItemType("CDrawImage"));
}

void FlowChartWindow::load(QString libName)
{
    QString dll;
    {

#ifdef QT_DEBUG
        {
#ifdef linux
            dll = QApplication::applicationDirPath()+QString("/lib%1d.so").arg(libName);
#else
            dll = QApplication::applicationDirPath()+QString("/%1d.dll").arg(libName);
#endif

        }
#else
        {
#ifdef linux
            dll = QApplication::applicationDirPath()+QString("/lib%1.so").arg(libName);
#else
            dll = QApplication::applicationDirPath()+QString("/%1.dll").arg(libName);
#endif
        }
#endif
        qDebug()<<dll;
        QLibrary lib(dll);
        if(!lib.isLoaded())
        {
            lib.load();
        }
    }
}

void FlowChartWindow::slot_CurrentChanged(QString  oldId,QString currentId)
{
    ItemAttrPtr ptr = m_Managment->getItemAttr(currentId);
    if(!ptr.isNull())
    {
        m_PropertyWidget->SetAllProperty(ptr->attrs);
    }
    else
    {
        m_PropertyWidget->SetAllProperty(m_Managment->getViewAttr());
    }

}

void FlowChartWindow::createMenu()
{

    QList<QString> comNames;
    QList<QString> comsequences;
    QList<const char *> comfuns;
    comNames<<tr("编辑")<<tr("结束编辑")<<tr("删除")<<tr("顶置");
    comfuns<<SLOT(slot_Edit())<<SLOT(slot_EditEnd())<<SLOT(slot_Delete())<<SLOT(slot_SetZValue());
    m_Menus.insert(OtherItem,GuiHanle::createMenu(comNames,comsequences,comfuns,this));

    QList<QString> actionNames;
    QList<QString> sequences;
    QList<const char *> funs;
    actionNames<<tr("测试")<<tr("画线")<<tr("保存");
    funs<<SLOT(slot_Test())<<SLOT(slot_EditFold())<<SLOT(slot_Save());
    m_Menus.insert(Background,GuiHanle::createMenu(actionNames,sequences,funs,this));

    actionNames.clear();
    sequences.clear();
    funs.clear();

    actionNames<<tr("插入点")<<tr("删除点")<<comNames;
    funs<<SLOT(slot_InsterPoint())<<SLOT(slot_DeletePoint())<<comfuns;
    m_Menus.insert(FlodLine,GuiHanle::createMenu(actionNames,sequences,funs,this));

    actionNames.clear();
    sequences.clear();
    funs.clear();
    m_AlignmentAction = new QAction(tr("对齐"),this);
    actionNames<<tr("水平")<<tr("垂直");
    funs<<SLOT(slot_HorizontalAlignment())<<SLOT(slot_VerticalAlignment());
    m_AlignmentAction->setMenu(GuiHanle::createMenu(actionNames,sequences,funs,this));


}

void FlowChartWindow::handFoldLine(int handle)
{
    int index=m_Managment->upDateToolData(m_Managment->getCurrentId(),"ItemFoldRegard",(void *)Dr::Find).toInt();
    if(index !=-1 && handle == Dr::Insert)
    {
        m_Managment->setEdit(CZDRAW::Edit);
    }
    QList<int> *tmp = new QList<int>;
    (*tmp)<<handle<<index;
    m_Managment->upDateToolData(m_Managment->getCurrentId(),"EditFoldLine",(void *)tmp).toBool();
    delete tmp;
}

void FlowChartWindow::AlignmentType(QString type)
{
    m_Managment->upDateToolData(m_Managment->getCurrentId(),"AlignmentTool",(void *)&type);
}



void FlowChartWindow::contextMenuEvent(QContextMenuEvent *)
{
    QMenu * menu = NULL;
    ItemAttrPtr ptr = m_Managment->getCurrentAttr();
    if(ptr.isNull() && !m_Managment->getEdit())
    {
        menu = m_Menus.value(Background);
    }
    else if(!ptr.isNull() && ptr->className == "FoldLine")
    {
        QList<QString> actionNames;
        menu = m_Menus.value(FlodLine);
        actionNames<<tr("插入点")<<tr("编辑")<<tr("删除点");
        foreach (QAction* action, menu->actions())
        {
            if(actionNames.contains(action->text()))
            {
                action->setEnabled(!m_Managment->getEdit());
            }
        }
    }
    else
    {
        QList<QString> actionNames;
        menu = m_Menus.value(OtherItem);
        actionNames<<tr("编辑")<<tr("顶置");
        foreach (QAction* action, menu->actions())
        {
            if(actionNames.contains(action->text()))
            {
                action->setEnabled(!m_Managment->getEdit());
            }
        }
    }
    if(m_Managment->getSelects().size() > 1)
    {
        menu->addAction(m_AlignmentAction);
    }
    else
    {
        menu->removeAction(m_AlignmentAction);
    }
    if(menu)
    {
        menu->exec(QCursor::pos());
    }
}
