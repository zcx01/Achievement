#include "BaseDrawObject.h"
#include "./DrawToolInclude/CZDrawInclude.h"
#include "hfdefine.h"

BaseDrawObject::BaseDrawObject(QWidget *parent) : QObject(parent)
{
//    m_Menu = NULL;
}

BaseDrawObject::~BaseDrawObject()
{
//    D_Delete(m_Menu);
    D_Delete(m_DrawObj);
}

bool BaseDrawObject::InitManagement(QString configDirPath, QLayout *layout)
{
    CZDrawManagement* managment = new CZDrawManagement;
    try
    {
        if(!loadConfigFile(configDirPath,managment))
        {
            m_ToolFileName = configDirPath+"/ToolConfig.xml";
            managment->loadTool(m_ToolFileName);

            m_ItemToolFileName = configDirPath+"/ItemToolConfig.xml";
            managment->configItemTool(m_ItemToolFileName);

            m_ItemFileName = configDirPath+"/ItemConfig.xml";
            managment->loadItemFileName(m_ItemFileName);
        }


        m_DrawObj = managment;

        ConnectSig(true);

        if(layout)
        {
            layout->addWidget(managment->getWidget());
        }
        else
        {
            throw;
        }

    }
    catch (...)
    {
        return false;
    }

    return true;

}

void BaseDrawObject::contextMenuEvent(QContextMenuEvent *event)
{

}

bool BaseDrawObject::loadConfigFile(QString configDirPath,CZDrawManagement* m)
{
    return false;
}

void BaseDrawObject::ConnectSig(const bool &state)
{

}

bool BaseDrawObject::CreateItem(const QString &id, const QString &className, const QVariantMap *selfAttr)
{
    DrawItemAttrPtr ptr = m_DrawObj->getItemAttr(id);
    if(ptr.isNull())
    {
        QVariantMap attr;
        attr.insert(IDD,id);
        m_DrawObj->createItem(className,attr);
    }

    ptr = m_DrawObj->getItemAttr(id);

    if(ptr.isNull())
    {
        return false;
    }

    for(auto iter = selfAttr->begin(); iter != selfAttr->end(); iter++)
    {
        ptr->attrs.insert(iter.key(),iter.value());
    }

    return m_DrawObj->upDateItemAttr(ptr);
}

QMenu *BaseDrawObject::createMenu(QList<QString> actionNames, QList<QString> sequences, QList<const char *> funs, QObject *receive, QList<int> separators)
{
    QMenu *pMenu = new QMenu();
    for(int i =0; i < actionNames.size(); i++)
    {
        QString actionName = actionNames.at(i);
        QAction *action = new QAction(actionName,pMenu);
        if(sequences.size() >i)
            action->setShortcut(QKeySequence(sequences.at(i)));
            //createShortcut(action,sequences.at(i),receive);
        if(funs.size() > i)
            QObject::connect(action,SIGNAL(triggered()),receive,funs.at(i));
        pMenu->addAction(action);
        if(separators.contains(i))
            pMenu->addSeparator();
    }
    return pMenu;
}

void BaseDrawObject::Save()
{
    m_DrawObj->saveItemFile(m_ItemFileName);
    m_DrawObj->saveTool(m_ToolFileName);
    m_DrawObj->saveConfigItemTool(m_ItemToolFileName);
}
