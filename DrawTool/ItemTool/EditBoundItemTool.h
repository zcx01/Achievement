#ifndef EDITBOUNDITEMTOOL_H
#define EDITBOUNDITEMTOOL_H

/*******************************************************
    created     :   2019/08/21
    file base	:   EditBoundItemTool.h
    author      :   zcx
    purpose     :	编辑大小
*******************************************************/
#include "CZBaseTool.h"

class EditBoundItemTool : public CZBaseTool
{
    Q_OBJECT
public:
    explicit EditBoundItemTool(QObject *parent = nullptr);
    virtual QString getClassName();
    virtual void upDataTool(CZBase *item);
    void setEditItem(CZDRAW::EditStatus state, CZBase *item);
    void removeItem(CZBase *item);
signals:

public slots:

    // CZBaseTool interface
protected:
    virtual bool viewMousePressEvent(QMouseEvent *event);
    virtual bool viewMouseReleaseEvent(QMouseEvent *event);
    virtual bool viewMouseMoveEvent(QMouseEvent *event);
private:
    void init(bool isActiva);

    bool CompPoint(QPointF p1,QPointF p2);

    CZBase *            m_CurrentItem;  //当前的图元
    bool                m_PressLeft;    //鼠标左键按下
};

#endif // EDITBOUNDITEMTOOL_H
