#ifndef CMANAGMENTTOOL_H
#define CMANAGMENTTOOL_H

#include <QObject>
#include <QWidget>
#include "czdrawstruct.h"
class CZBaseTool;
class CZBase;
class CManagementTool : public QObject
{
    Q_OBJECT
public:
    explicit CManagementTool(QObject *parent = nullptr);
    ~CManagementTool();

    /**
    * @fn       loadTool(QString fileName);
    * @brief    加载工具
    * @date     2019/07/31
    * @author   zcx
    * @param    fileName:文件名
    * @return   是否成功
    */
    bool loadTool(QString fileName);

    /**
    * @fn       saveTool(QString fileName);
    * @brief    保存工具的配置文件
    * @author	zcx
    * @date     2019/12/21
    * @param	fileName:文件名
    * @return	是否成功
    */
    bool saveTool(QString fileName);

    /**
    * @fn       configItemTool(QString fileName);
    * @brief    配置item的工具,此函数要位于loadTool(QString fileName);之后
    * @date     2019/07/31
    * @author   zcx
    * @param    fileName:文件名
    * @return   是否成功
    */
    bool configItemTool(QString fileName);

    /**
    * @fn       saveConfigItemTool(QString fileName);
    * @brief    保存配置item的工具
    * @author	zcx
    * @date     2019/12/21
    * @param	fileName:文件名
    * @return	是否成功
    */
    bool saveConfigItemTool(QString fileName);

    /**
    * @fn       createTool(QString toolClassName);
    * @brief    创建一个工具
    * @author	zcx
    * @date     2019/12/21
    * @param	toolClassName:工具的名字
    * @return	无
    */
    void createTool(QString toolClassName);

    /**
    * @fn       getTools(QString itemType);
    * @brief    得到一个工具集合
    * @date     2019/07/13
    * @author   zcx
    * @param    className:item的类型
    * @return   工具集合
    */
    QList<CZBaseTool*> getTools(QString itemType);

    /**
    * @fn       getTypesByToolClassName(QString toolClassName);
    * @brief    通过工具的类名得到所有的所属该工具的item类型
    * @author	zcx
    * @date     2019/11/29
    * @param	toolClassName:类名
    * @return	item类型集合
    */
    QStringList getTypesByToolClassName(QString toolClassName);

    /**
    * @fn       getAllTool();
    * @brief    得到所有的工具
    * @date     2019/07/17
    * @author   zcx
    * @param    无
    * @return   工具集合
    */
    QList<CZBaseTool*> getAllTool();

    /**
    * @fn       getTool(QString toolClassName);
    * @brief    得到工具
    * @date     2019/07/17
    * @author   zcx
    * @param    toolClassName:工具的类名
    * @return   工具
    */
    CZBaseTool* getTool(QString toolClassName);


    /**
    * @fn       upDateAllTool();
    * @brief    初始化使用使用工具
    * @date     2019/07/26
    * @author   zcx
    * @param    无
    * @return   无
    */
    void initAllTool();

    /**
    * @fn       upDateTool(const QString toolClassName,CZBase *item);
    * @brief    更新指定工具
    * @date     2019/07/26
    * @author   zcx
    * @param    toolClassName:工具的类名 item:图元
    * @return   无
    */
    void upDateTool(const QString toolClassName,CZBase *item);

    /**
    * @fn       upDateTypeTool(const QString &itemType,CZBase *item);
    * @brief    更新一个类类型的工具
    * @date     2019/07/26
    * @author   zcx
    * @param    className:item的类名 item:图元
    * @return   无
    */
    void upDateTypeTool(CZBase *item);

    /**
    * @fn       getId();
    * @brief    得到标识
    * @date     2019/07/28
    * @author   zcx
    * @param    无
    * @return   标识
    */
    QString getId();

    /**
    * @fn       clear();
    * @brief    清除工具
    * @date     2019/07/31
    * @author   zcx
    * @param    无
    * @return   无
    */
    void clear();

    /**
    * @fn       setEditItem(const CZDRAW::EditStatus  &state,CZBase *item);
    * @brief    设置编辑的状态
    * @author	zcx
    * @date     2019/12/21
    * @param    state:编辑的状态 item:状态对应的图元
    * @return   无
    */
    void setEditItem(const CZDRAW::EditStatus &state, CZBase *item);

    /**
    * @fn       addItemToTool(const QString &itemType,const QString &toolClassName);
    * @brief    添加item到指定的工具中,添加加失败有std::logic_error异常抛出
    * @author	zcx
    * @date     2019/12/21
    * @param    itemType:图元的类型 toolClassName:工具的类名
    * @return   无
    */
    void addItemToTool(const QString &itemType, const QString &toolClassName);

signals:

public slots:

private:
    //注册回调函数
    void registerCallBackFun();

    QList<CZBaseTool*>                      m_Tools;             //工具集合
    QHash<QString,QList<CZBaseTool*>>       m_ItemHaveTools;     //一个类的item拥有的tool集合
    QString                                 m_Id;                //标识(时间传递使用传递)

protected:
    static bool itemSceneEventFilter(QGraphicsItem *watched, QEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemSceneEvent(QEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemContextMenuEvent(QGraphicsSceneContextMenuEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemDragEnterEvent(QGraphicsSceneDragDropEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemDragLeaveEvent(QGraphicsSceneDragDropEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemDragMoveEvent(QGraphicsSceneDragDropEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemDropEvent(QGraphicsSceneDragDropEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemFocusInEvent(QFocusEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemFocusOutEvent(QFocusEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemHoverEnterEvent(QGraphicsSceneHoverEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemHoverMoveEvent(QGraphicsSceneHoverEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemHoverLeaveEvent(QGraphicsSceneHoverEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemKeyPressEvent(QKeyEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemKeyReleaseEvent(QKeyEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemMousePressEvent(QGraphicsSceneMouseEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemMouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemWheelEvent(QGraphicsSceneWheelEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemInputMethodEvent(QInputMethodEvent *event, CZBase *sourceItem,CManagementTool* managementTool);
    static bool itemItemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value, CZBase *sourceItem,CManagementTool* managementTool);


    static bool viewEvent(QEvent *event,CManagementTool* managementTool);
    static bool viewCustomEvent(QEvent *event,CManagementTool* managementTool);
    static bool viewMousePressEvent(QMouseEvent *event,CManagementTool* managementTool);
    static bool viewMouseReleaseEvent(QMouseEvent *event,CManagementTool* managementTool);
    static bool viewMouseDoubleClickEvent(QMouseEvent *event,CManagementTool* managementTool);
    static bool viewMouseMoveEvent(QMouseEvent *event,CManagementTool* managementTool);
    static bool viewWheelEvent(QWheelEvent *event,CManagementTool* managementTool);
    static bool viewKeyPressEvent(QKeyEvent *event,CManagementTool* managementTool);
    static bool viewKeyReleaseEvent(QKeyEvent *event,CManagementTool* managementTool);
    static bool viewFocusInEvent(QFocusEvent *event,CManagementTool* managementTool);
    static bool viewFocusOutEvent(QFocusEvent *event,CManagementTool* managementTool);
    static bool viewEnterEvent(QEvent *event,CManagementTool* managementTool);
    static bool viewLeaveEvent(QEvent *event,CManagementTool* managementTool);
    static bool viewPaintEvent(QPaintEvent *event,CManagementTool* managementTool);
    static bool viewMoveEvent(QMoveEvent *event,CManagementTool* managementTool);
    static bool viewResizeEvent(QResizeEvent *event,CManagementTool* managementTool);
    static bool viewCloseEvent(QCloseEvent *event,CManagementTool* managementTool);
    static bool viewContextMenuEvent(QContextMenuEvent *event,CManagementTool* managementTool);
    static bool viewDragEnterEvent(QDragEnterEvent *event,CManagementTool* managementTool);
    static bool viewDragMoveEvent(QDragMoveEvent *event,CManagementTool* managementTool);
    static bool viewDragLeaveEvent(QDragLeaveEvent *event,CManagementTool* managementTool);
    static bool viewDropEvent(QDropEvent *event,CManagementTool* managementTool);
    static bool viewShowEvent(QShowEvent *event,CManagementTool* managementTool);
    static bool viewHideEvent(QHideEvent *event,CManagementTool* managementTool);
    static bool viewInputMethodEvent(QInputMethodEvent *event,CManagementTool* managementTool);
    static bool viewFocusNextPrevChild(bool next,CManagementTool* managementTool);


};

#endif // CMANAGMENTTOOL_H
