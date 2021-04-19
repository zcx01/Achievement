#ifndef CMANAGMENTITEM_H
#define CMANAGMENTITEM_H

#include <QObject>
#include "czdrawstruct.h"
#include <QGraphicsItem>
#include "CGraphicsView.h"
#include "cdraw_global.h"
class CGraphicsScene;
class CZBase;
class CDRAW_EXPORT CManagementItem : public CGraphicsView
{
    Q_OBJECT

public:
    explicit CManagementItem(QWidget *parent = nullptr);
    ~CManagementItem();

    /**
    * @fn       createItem(QString className,const QVariantMap &attr);
    * @brief    创建一个绘图的item
    * @date     2019/07/18
    * @author   zcx
    * @param    className:类名 attr:属性
    * @return
    */
    CZBase* createItem(QString className, const QVariantMap &attr);

    /**
    * @fn       deleteItem(QString id);
    * @brief    删除item
    * @date     2019/07/18
    * @author   zcx
    * @param    id:item的id
    * @return   是否成功
    */
    bool deleteItem(QString id);

    /**
    * @fn       setEdit(CZBase *item,const bool &state);
    * @brief    设置是否开启编辑
    * @date     2019/07/25
    * @author   zcx
    * @param    item:编辑的图元 state:编辑
    * @return   无
    */
    void setEdit(CZBase *item, const CZDRAW::EditStatus &state);

    /**
    * @fn       getIsEdit();
    * @brief    是否编辑
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   编辑
    */
    CZDRAW::EditStatus getEdit();

    /**
    * @fn       setSelects(QList<CZBase*  > items);
    * @brief    设置选择的item
    * @date     2019/07/25
    * @author   zcx
    * @param    items:选择的item集合
    * @return   无
    */
    void setSelects(QList<CZBase*  > items);

    /**
    * @fn       addSelect(CZBase*   item);
    * @brief    添加一个选中的item
    * @date     2019/07/25
    * @author   zcx
    * @param    item:图元
    * @return   无
    */
    void addSelect(CZBase* item);

    /**
    * @fn       removeSelect(CZBase*   item);
    * @brief    移除一个选中
    * @date     2019/07/25
    * @author   zcx
    * @param    item:图元
    * @return   无
    */
    void removeSelect(CZBase*   item);

    /**
    * @fn       clearSelect();
    * @brief    清除所有选中
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   无
    */
    void clearSelect();

    /**
    * @fn       getSelects();
    * @brief    得到所有选中的item
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   所有选中的item
    */
    QList<CZBase*  > getSelects();

    /**
    * @fn       setCurrent(CZBase*   item);
    * @brief    设置当前图元
    * @date     2019/07/25
    * @author   zcx
    * @param    item:图元
    * @return   无
    */
    void setCurrent(CZBase*   item);

    /**
    * @fn       getCurrent();
    * @brief    得到当前图元
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   item
    */
    CZBase*   getCurrent();

    /**
    * @fn       addItem(CZBase*   item);
    * @brief    添加一个图元
    * @date     2019/07/25
    * @author   zcx
    * @param    item:图元
    * @return   无
    */
    void addItem(CZBase*   item);


    /**
    * @fn       clearItem(const bool &clearBackgound = true);
    * @brief    清除所有的图元
    * @date     2019/07/30
    * @author   zcx
    * @param    clearBackgound:是否清除背景
    * @return   无
    */
    void clearItem(const bool &clearBackgound = true);

    /**
    * @fn       getItems();
    * @brief    得到所有的item
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   图元集合
    */
    QList<CZBase*  > getItems();

    /**
    * @fn       getItemById(QString id);
    * @brief    通过Id得到一个item
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   图元
    */
    CZBase* getItemById(QString id);

    /**
    * @fn       setEventId(const QString &id);
    * @brief    设置时间的标识
    * @date     2019/07/28
    * @author   zcx
    * @param    id:标识
    * @return   无
    */
    void setEventId(const QString &id);

    /**
    * @fn       setViewAttr(const QVariantMap &attr);
    * @brief    设置视图的属性
    * @date     2019/07/29
    * @author   zcx
    * @param    视图的属性
    * @return   无
    */
    void setViewAttr(const QVariantMap &attrs);

    /**
    * @fn       getViewAttr();
    * @brief    得到视图的属性
    * @date     2019/07/29
    * @author   zcx
    * @param    无
    * @return   视图的属性
    */
    QVariantMap getViewAttr();

    /**
    * @fn       getAttrByItemType(const QString &itemType);
    * @brief    通过类型得到属性
    * @date     2019/08/01
    * @author   zcx
    * @param    无
    * @return   属性
    */
    QVariantMap getAttrByItemType(const QString &itemType);

    /**
    * @fn       getKeyType(const QString &id,const QString &key);
    * @brief    得到一个键值的类型
    * @author	zcx
    * @date     2019/12/20
    * @param	id:标识 key:键值
    * @return	类型
    */
    QVariant::Type getKeyType(const QString &id,const QString &key);

    /**
     * @brief 发送创建一共图元
     * @param data:数据
     */
    void SendCreateItem(const QVariantMap &data);

    /**
     * @brief 发射自定义属性
     * @param id:标识
     * @param data:数据
     */
    void SendCustomAttr(const QString &id,const QVariant &data);
signals:

    //当前选择改变
    void sig_CurrentChanged(CZBase*  old,CZBase* current);

    //创建item
    void sig_CreateItem(const QVariantMap &data);

    //发射自定义属性
    void sig_SendCustomAttr(const QString &id,const QVariant &data);

public slots:


private:   
    void initData();

    //移除容器中一个item
    void removeItem(CZBase*   item);

    CZBase*                     m_CurrentItem;       //当前item
    QHash<QString,CZBase*>      m_Items;             //所有item集合
    CZDRAW::EditStatus          m_Edit;              //是否是编辑
    QString                     m_EventId;           //事件的标识
    QHash<QString,QVariantMap>  m_ItemTypeAttr;      //类型关联的属性

    // QObject interface
public:
    virtual bool event(QEvent *event);
    virtual void customEvent(QEvent *event);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void inputMethodEvent(QInputMethodEvent *event);
    virtual bool focusNextPrevChild(bool next);

    // QAbstractScrollArea interface
protected:
    virtual void scrollContentsBy(int dx, int dy);
};

#endif // CMANAGMENTITEM_H
