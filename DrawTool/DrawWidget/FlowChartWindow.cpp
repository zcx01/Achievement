#include "FlowChartWindow.h"
#include <QDebug>
#include "../DrawToolInclude/CZDrawInclude.h"

FlowChartWindow::FlowChartWindow(QWidget *parent) :
    BaseDrawObject(parent)
{
    //创建菜单
    createMenu();

}

FlowChartWindow::~FlowChartWindow()
{
}

void FlowChartWindow::slot_Test()
{

}

void FlowChartWindow::slot_NewItem(QString type)
{
    slot_EditEnd();
    QString id = m_DrawObj->createItemByType(type);
    if(id.isEmpty()) return;
    m_DrawObj->setCurrentId(id);
    m_DrawObj->setEdit(CZDRAW::NewBulid);
}

void FlowChartWindow::slot_Edit()
{
    m_DrawObj->setEdit(CZDRAW::Edit);
}

void FlowChartWindow::slot_EditEnd()
{
    m_DrawObj->setEdit(CZDRAW::NoEdit);
    m_DrawObj->upDateTool("DisPlayName",m_DrawObj->getCurrentId());
}

void FlowChartWindow::slot_EditFold()
{
    QVariantMap attrs;
    attrs.insert(SCALE,1);
    attrs.insert(PENS,"0|255,0,0,255|1");
    attrs.insert(FOLDARROWSSTYLE,"SealTriangle");
    attrs.insert(FOLDNODEBRUSH,"255,255,0,255|1");
    attrs.insert(FOLDANODESTYLE,"1");
    QString id = m_DrawObj->createItem("FoldLine",attrs);
    m_DrawObj->setCurrentId(id);
    m_DrawObj->setEdit(CZDRAW::Edit);
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
    m_DrawObj->upDateToolData(m_DrawObj->getCurrentId(),"ColldingZValue",NULL).toInt();
}

void FlowChartWindow::slot_Delete()
{
    m_DrawObj->deleteItem(m_DrawObj->getCurrentId());
}

void FlowChartWindow::slot_Save()
{
    Save();
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
    if(attr == BOUNDRECT && m_DrawObj->getEdit() == CZDRAW::NoEdit)
    {
        m_DrawObj->upDateTool("DisPlayName",id);
    }
    //  qDebug()<<m_DrawObj->getViewAttr();
}

void FlowChartWindow::slot_CurrentChanged(QString  oldId,QString currentId)
{
    DrawItemAttrPtr ptr = m_DrawObj->getItemAttr(currentId);

}

void FlowChartWindow::createMenu()
{

    QList<QString> comNames;
    QList<QString> comsequences;
    QList<const char *> comfuns;
    comNames<<tr("编辑")<<tr("结束编辑")<<tr("删除")<<tr("顶置");
    comfuns<<SLOT(slot_Edit())<<SLOT(slot_EditEnd())<<SLOT(slot_Delete())<<SLOT(slot_SetZValue());
    m_Menus.insert(OtherItem,BaseDrawObject::createMenu(comNames,comsequences,comfuns,this));

    QList<QString> actionNames;
    QList<QString> sequences;
    QList<const char *> funs;
    actionNames<<tr("测试")<<tr("画线")<<tr("保存");
    funs<<SLOT(slot_Test())<<SLOT(slot_EditFold())<<SLOT(slot_Save());
    m_Menus.insert(Background,BaseDrawObject::createMenu(actionNames,sequences,funs,this));

    actionNames.clear();
    sequences.clear();
    funs.clear();

    actionNames<<tr("插入点")<<tr("删除点")<<comNames;
    funs<<SLOT(slot_InsterPoint())<<SLOT(slot_DeletePoint())<<comfuns;
    m_Menus.insert(FlodLine,BaseDrawObject::createMenu(actionNames,sequences,funs,this));

    actionNames.clear();
    sequences.clear();
    funs.clear();
    m_AlignmentAction = new QAction(tr("对齐"),this);
    actionNames<<tr("水平")<<tr("垂直");
    funs<<SLOT(slot_HorizontalAlignment())<<SLOT(slot_VerticalAlignment());
    m_AlignmentAction->setMenu(BaseDrawObject::createMenu(actionNames,sequences,funs,this));
}

void FlowChartWindow::ConnectSig(const bool &state)
{
    if(state)
    {
        //添加属性窗体

        connect(m_DrawObj,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_AttrChanged(QString,QString)));
        connect(m_DrawObj,SIGNAL(sig_CurrentChanged(QString,QString)),this,SLOT(slot_CurrentChanged(QString,QString)));
    }
}

void FlowChartWindow::handFoldLine(int handle)
{
    int index=m_DrawObj->upDateToolData(m_DrawObj->getCurrentId(),"ItemFoldRegard",(void *)Dr::Find).toInt();
    if(index !=-1 && handle == Dr::Insert)
    {
        m_DrawObj->setEdit(CZDRAW::Edit);
    }
    QList<int> *tmp = new QList<int>;
    (*tmp)<<handle<<index;
    m_DrawObj->upDateToolData(m_DrawObj->getCurrentId(),"EditFoldLine",(void *)tmp).toBool();
    delete tmp;
}

void FlowChartWindow::AlignmentType(QString type)
{
    m_DrawObj->upDateToolData(m_DrawObj->getCurrentId(),"AlignmentTool",(void *)&type);
}

void FlowChartWindow::contextMenuEvent(QContextMenuEvent *)
{
    QMenu * menu = NULL;
    DrawItemAttrPtr ptr = m_DrawObj->getCurrentAttr();
    if(ptr.isNull() && !m_DrawObj->getEdit())
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
                action->setEnabled(!m_DrawObj->getEdit());
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
                action->setEnabled(!m_DrawObj->getEdit());
            }
        }
    }
    if(m_DrawObj->getSelects().size() > 1)
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
MYREGISTER(FlowChartWindow)
