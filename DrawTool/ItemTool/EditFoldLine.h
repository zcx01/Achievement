#ifndef EDITFOLDLINE_H
#define EDITFOLDLINE_H
/*******************************************************
    created		:	2019/12/03
    file base   :	EditFoldLine.h
    author		:	zcx
    purpose		:	编辑折线
*******************************************************/
#include "CZBaseTool.h"

class EditFoldLine : public CZBaseTool
{
    Q_OBJECT
public:
    explicit EditFoldLine(QObject *parent = NULL);

signals:

public slots:

    // CZBaseTool interface
public:
    QString getClassName();
    void upDataTool(CZBase *item);
    void removeItem(CZBase *item);

    QVariant dealData(CZBase *item, void *pData);

    void setEditItem(CZDRAW::EditStatus state, CZBase *item);
    // CZBaseTool interface
protected:
    virtual bool viewMousePressEvent(QMouseEvent *event);
    virtual bool viewMouseReleaseEvent(QMouseEvent *event);
    virtual bool viewMouseMoveEvent(QMouseEvent *event);

private:
    //删除一个点
    void DeletePoint(int index);

    void AddOrModifyPoint(int index, QPointF pos, int hand);

    void init(bool isActiva);

    CZBase *        m_CurrentItem;  //当前的图元
    bool            m_IsAdd;        //鼠标左键按下
    int             m_CurrentIndex; //当前的点
    bool            m_IsInsert;     //是否是插入
};

#endif // EDITFOLDLINE_H
