#ifndef CZBASETOOL_H
#define CZBASETOOL_H
/*******************************************************
    created     :   2019/07/09
    file base	:   CZBaseTool.h
    author      :   zcx
    purpose     :	工具的父类
*******************************************************/

#include <QObject>
#include "CZBase.h"
#include <QWidget>
#include "cdraw_global.h"
class CManagementItem;
class CDRAW_EXPORT CZBaseTool : public QObject
{
    Q_OBJECT
    friend class CManagementTool;
    // CZBaseTool interface
    //被操作的item的传递过来的事件，要设置激活才会传递事件
protected:
    virtual bool itemSceneEventFilter(QGraphicsItem *watched, QEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemSceneEvent(QEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemContextMenuEvent(QGraphicsSceneContextMenuEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemDragEnterEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemDragLeaveEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemDragMoveEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemDropEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemFocusInEvent(QFocusEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemFocusOutEvent(QFocusEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemHoverEnterEvent(QGraphicsSceneHoverEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemHoverMoveEvent(QGraphicsSceneHoverEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemHoverLeaveEvent(QGraphicsSceneHoverEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemKeyPressEvent(QKeyEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemKeyReleaseEvent(QKeyEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemMousePressEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemMouseMoveEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemMouseDoubleClickEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemWheelEvent(QGraphicsSceneWheelEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemInputMethodEvent(QInputMethodEvent *event,QGraphicsItem *sourceItem);
    virtual bool itemInputMethodQuery(Qt::InputMethodQuery query,QGraphicsItem *sourceItem) const;
    virtual bool itemItemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value,QGraphicsItem *sourceItem);

    virtual bool viewEvent(QEvent *event);
    virtual bool viewCustomEvent(QEvent *event);
    virtual bool viewMousePressEvent(QMouseEvent *event);
    virtual bool viewMouseReleaseEvent(QMouseEvent *event);
    virtual bool viewMouseDoubleClickEvent(QMouseEvent *event);
    virtual bool viewMouseMoveEvent(QMouseEvent *event);
    virtual bool viewWheelEvent(QWheelEvent *event);
    virtual bool viewKeyPressEvent(QKeyEvent *event);
    virtual bool viewKeyReleaseEvent(QKeyEvent *event);
    virtual bool viewFocusInEvent(QFocusEvent *event);
    virtual bool viewFocusOutEvent(QFocusEvent *event);
    virtual bool viewEnterEvent(QEvent *event);
    virtual bool viewLeaveEvent(QEvent *event);
    virtual bool viewPaintEvent(QPaintEvent *event);
    virtual bool viewMoveEvent(QMoveEvent *event);
    virtual bool viewResizeEvent(QResizeEvent *event);
    virtual bool viewCloseEvent(QCloseEvent *event);
    virtual bool viewContextMenuEvent(QContextMenuEvent *event);
    virtual bool viewDragEnterEvent(QDragEnterEvent *event);
    virtual bool viewDragMoveEvent(QDragMoveEvent *event);
    virtual bool viewDragLeaveEvent(QDragLeaveEvent *event);
    virtual bool viewDropEvent(QDropEvent *event);
    virtual bool viewShowEvent(QShowEvent *event);
    virtual bool viewHideEvent(QHideEvent *event);
    virtual bool viewInputMethodEvent(QInputMethodEvent *event);
    virtual bool viewFocusNextPrevChild(bool next);
public:
    CZBaseTool(QObject *parnet = NULL);
    ~CZBaseTool();

    /**
    * @fn       setOperationItems(QList<CZBase*> items);
    * @brief    设置被操作的item的集合
    * @date     2019/07/10
    * @author   zcx
    * @param    item:被操作的item的集合
    * @return   无
    */
    void setOperationItems(QList<CZBase *> items);

    /**
    * @fn       addOperationItem(CZBase *item);
    * @brief    添加要操作的item
    * @date     2019/07/13
    * @author   zcx
    * @param    item:要操作的item
    * @return   无
    */
    void addOperationItem(CZBase * item);

    /**
    * @fn       removeOperationItem(CZBase *item);
    * @brief    移除要操作的item
    * @date     2019/07/13
    * @author   zcx
    * @param    item:要操作的item
    * @return   无
    */
    void removeOperationItem(CZBase *item);

    /**
    * @fn       getItemById(const QString &id);
    * @brief    得到item通过id
    * @date     2019/07/26
    * @author   zcx
    * @param    id:item标识
    * @return   图元
    */
    CZBase* getItemById(const QString &id);

    /**
    * @fn       getOperationItems();
    * @brief    得到被操作的item
    * @date     2019/07/10
    * @author   zcx
    * @param    无
    * @return   被操作的item
    */
    QList<CZBase*> getOperationItems();

    /**
    * @fn       setDealData(QGraphicsItem *item,void *pData);
    * @brief    设置要处理的数据
    * @date     2019/07/12
    * @author   zcx
    * @param    pData:数据
    * @return   处理后的数据
    */
    QVariant setDealData(CZBase *item,void *pData);

    /**
    * @fn       setToolActiva(bool state);
    * @brief    设置是否激活
    * @date     2019/07/10
    * @author   zcx
    * @param    state:是否激活
    * @return   无
    */
    void setToolActiva(bool state);

    /**
    * @fn       getToolActiva();
    * @brief    得到是否激活
    * @date     2019/07/10
    * @author   zcx
    * @param    无
    * @return   是否激活
    */
    bool getToolActiva();

    /**
    * @fn       setManagment(CManagementItem *managmentItem);
    * @brief    设置
    * @date     2019/08/03
    * @author   zcx
    * @param    managmentItem:设置item的管理类
    * @return   无
    */
    void setManagment(CManagementItem *managmentItem);

    /**
    * @fn       getClassName(QString id) = 0;
    * @brief    得到类名
    * @date     2019/07/10
    * @author   zcx
    * @param    无
    * @return   唯一标识
    */
    virtual QString getClassName() = 0;

    /**
    * @fn       initTool();
    * @brief    初始化工具,默认调用upDataTool(CZBase *item);会把所有的item传递
    * @date     2019/07/26
    * @author   zcx
    * @param    2019/07/26
    * @return   无
    */
    virtual void initTool();

    /**
    * @fn       upDataTool(CZBase *item);
    * @brief    更新工具
    * @date     2019/08/24
    * @author   zcx
    * @param    item:指定的item
    * @return   无
    */
    virtual void upDataTool(CZBase *item)=0;

    /**
    * @fn       isBelong(CZBase* item);
    * @brief    是否属于该工具
    * @date     2019/08/11
    * @author   zcx
    * @param    item:图元
    * @return   是否属于
    */
    bool isBelong(CZBase* item);

    /**
    * @fn       setEditItem(CZDRAW::EditStatus state, CZBase* item);
    * @brief    设置编辑的item
    * @author	zcx
    * @date     2019/11/29
    * @param	state:是否编辑 item:指定的item
    * @return	无
    */
    virtual void setEditItem(CZDRAW::EditStatus state, CZBase* item);


    /**
    * @fn       dealMinData(CZBase* item,const QVariant &pData);
    * @brief    处理小数据
    * @author	zcx
    * @date     2020/5/20
    * @param	item:指定的item pData:数据
    * @return	处理后的数据
    */
    virtual QVariant dealMinData(CZBase* item,const QVariant &pData);

protected:
    //添加图元
    virtual void addItem(CZBase *item);

    //移除图元
    virtual void removeItem(CZBase *item);

    //处理数据
    virtual QVariant dealData(CZBase *item,void *pData);

    QHash<QString,CZBase*>   m_OperationItems;       //要操作的item
    CManagementItem*         m_ManagmentItem;        //设置管理类
private:
    //初始化数据
    void initData();

    bool            m_IsActiva;             //此工具是否激活
};

#endif // CZBASETOOL_H
