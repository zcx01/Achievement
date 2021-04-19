#ifndef DISPLAYNAME_H
#define DISPLAYNAME_H


/*******************************************************
    created     :   2019/08/21
    file base	:   DisPlayName.h
    author      :   zcx
    purpose     :	显示设置的文字
                    可以编辑字必须有|QGraphicsItem::ItemIsFocusable
*******************************************************/
#include "CZBaseTool.h"
class DisPlayName  : public CZBaseTool
{
    Q_OBJECT
public:
    DisPlayName();

    // CZBaseTool interface
    virtual QString getClassName();
    virtual void upDataTool(CZBase *item);
    virtual void removeItem(CZBase *item);

    virtual void setEditItem(CZDRAW::EditStatus state, CZBase *item);

    virtual bool itemKeyPressEvent(QKeyEvent *event, QGraphicsItem *sourceItem);

private slots:
    void slot_ContentsChanged(QGraphicsTextItem *textItem);

    void slot_BoundChanged(QString id,QString attr);

private:
    //QHash<CZBase*,QGraphicsSimpleTextItem *>    m_TextItems;
    QHash<CZBase*,QGraphicsTextItem *>    m_TextItems;
};

#endif // DISPLAYNAME_H
