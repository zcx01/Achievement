#ifndef CZBASE_H
#define CZBASE_H

/*******************************************************
    created     :   2019/09/10
    file base	:   CZBase.h
    author      :   zcx
    purpose     :	支持异步和同步处理
                    可以限定边界大小
                    (但是必须设定SceneSize和Flags必须有|QGraphicsItem::ItemSendsScenePositionChanges)
*******************************************************/
#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include "czdrawstruct.h"
#include "HfFrameReflect/cmyregistersingle.h"
#include "cdraw_global.h"

class CDRAW_EXPORT CZBase :  public  QGraphicsObject
{
    Q_OBJECT
protected:
    virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
    virtual bool sceneEvent(QEvent *event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
    virtual void inputMethodEvent(QInputMethodEvent *event);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    CZBase(QGraphicsItem *parnet = NULL);
    virtual ~CZBase();

    //重置顺序
    static void resetOrder();

    //得到一个添加顺序
    int getOrder();

    /**
    * @fn       loadFile(const QString &fileName,bool isAsyn = true);
    * @brief    异步（或者同步）加载配置文件
    * @date     2019/07/08
    * @author   zcx
    * @param    fileName:配置文件名
    * @return   是否加载成功,异步加载直接返回true
    */
    bool loadFile(const QString &fileName,bool isAsyn = true);

    //----------------------------属性-----------------------------------
    /**
    * @fn       setId(QString id);
    * @brief    设置标识
    * @date     2019/07/15
    * @author   zcx
    * @param    id:标识
    * @return   无
    */
    void setId(QString id);

    /**
    * @fn       getId();
    * @brief    得到标识
    * @date     2019/07/15
    * @author   zcx
    * @param    无
    * @return   标识
    */
    QString getId();

    /**
    * @fn       setAttrs(const QVariantMap &attrs);
    * @brief    设置所有属性
    * @date     2019/07/15
    * @author   zcx
    * @param    attrs:属性
    * @return   无
    */
    void setAttrs(const QVariantMap &attrs);

    /**
    * @fn       getAttrs()
    * @brief    得到属性
    * @date     2019/07/15
    * @author   zcx
    * @param    无
    * @return   得到属性
    */
    QVariantMap getAttrs();

    /**
    * @fn       getAttr(const QString &key);
    * @brief    得到对应的属性（比较快，但是不会触发getAttrUpdate()函数）
    * @date     2019/07/26
    * @author   zcx
    * @param    key:键值
    * @return   属性
    */
    //QVariant getAttr(const QString &key);

    /**
    * @fn       setAttr(const QString &key,const QVariant &attr);
    * @brief    设置key对应的属性
    * @date     2019/07/15
    * @author   zcx
    * @param    key:属性key attr:属性
    * @return   无
    */
    void setAttr(const QString &key,const QVariant &attr,bool isUpdateAll = false);

    /**
    * @fn       getClassName(QString id) = 0;
    * @brief    得到类名
    * @date     2019/07/10
    * @author   zcx
    * @param    无
    * @return   类名
    */
    virtual QString getClassName();

    /**
    * @fn       CZBase* getThis();
    * @brief    得到本类指针
    * @date     2019/07/18
    * @author   zcx
    * @param    无
    * @return   无
    */
    virtual QGraphicsItem* getThis();

    /**
    * @fn       boundingRect() const;
    * @brief    返回总的范围
    * @date     2019/07/25
    * @author   zcx
    * @param    无
    * @return   总的范围
    */
    virtual QRectF boundingRect() const;

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
    * @fn       setItemType(const QString &type);
    * @brief    设置图元的类型
    * @date     2019/07/31
    * @author   zcx
    * @param    type:图元的类型(如果没有定义，就等于类型)
    * @return   无
    */
    void setItemType(const QString &type);

    /**
    * @fn       getItemType();
    * @brief    得到图元的类型
    * @date     2019/07/31
    * @author   zcx
    * @param    无
    * @return   图元的类型
    */
    QString getItemType();

    /**
    * @fn       isAttrValueValid(const QString &key);
    * @brief    判断一个属性值是否有效
    * @author	zcx
    * @date     2019/12/19
    * @param	key:键值
    * @return	是否有效
    */
    bool isAttrValueValid(const QString &key);

    /**
    * @fn       getKeyType(const QString &key);
    * @brief    得到一个key的类型
    * @author	zcx
    * @date     2019/12/20
    * @param	key:键值
    * @return	类型
    */
    virtual QVariant::Type getKeyType(const QString &key);

    /**
     * @brief 添加到场景触发的函数
     * @param s:场景
     */
    virtual void AddScene(QGraphicsScene *s);

    //-----------------重写-------------------------------------
    void setPos(const QPointF &pos);
    void setPos(qreal x, qreal y);
    QPointF pos();
    void setRotation(qreal angle);
    qreal rotation();
    void setScale(qreal factor);
    qreal scale();
    void setAcceptDrops(bool on);
    bool acceptDrops();
    void setActive(bool active);
    bool isActive();
    void setEnabled(bool enabled);
    bool isEnabled();
    void setFlags(GraphicsItemFlags flags);
    GraphicsItemFlags flags();
    void setFocus(Qt::FocusReason focusReason = Qt::OtherFocusReason);
    bool hasFocus();
    void clearFocus();
    void setOpacity(qreal opacity);
    qreal opacity() ;
    void setX(qreal x);
    void setY(qreal y);
    void setToolTip(const QString &toolTip);
    QString toolTip() ;
    void setVisible(bool visible);
    bool isVisible() ;
    void setZValue(qreal z);
    qreal zValue();
    void setTransformOriginPoint(const QPointF &origin);
    bool isSelected();
    void setAcceptedMouseButtons(Qt::MouseButtons buttons);

    //-------------------------操作-----------------------------
    /**
    * @fn       upDateData(const QVariant &pData,bool isAsyn = true);
    * @brief    设置异步（或者同步）刷新的数据
    * @date     2019/07/08
    * @author   zcx
    * @param    pData:数据 isAsyn:是否异步
    * @return   无
    */
    void upDateData(const QVariant &pData,bool isAsyn = true);

    /**
    * @fn       getDateData();
    * @brief    得到更新的数据
    * @date     2019/07/08
    * @author   zcx
    * @param    无
    * @return   更新的数据
    */
    QVariant getDateData();

    /**
    * @fn       isContainMouseClickPos(QPointF pos);
    * @brief    是否包含点击的点,如果没有包含就不接受鼠标事件(会在调用items()后使用)
    * @author	zcx
    * @date     2019/12/19
    * @param	pos:点击的坐标(在场景中的)
    * @return	包含点击的点
    */
    bool isContainMousePos(QPointF pos);

    /**
    * @fn       setEdit(bool state);
    * @brief    设置是否编辑
    * @author	zcx
    * @date     2019/12/20
    * @param	state:是否编辑
    * @return	无
    */
    virtual void setEdit(CZDRAW::EditStatus state);

    /**
    * @fn       setBounding(QRectF &bound);
    * @brief    设置范围
    * @author	zcx
    * @date     2019/12/17
    * @param	bound:矩形
    * @return	无
    */
    void setBounding(QRectF bound);

    /**
    * @fn       sendAttrChanged(QString attrkey);
    * @brief    发送属性改变的信号
    * @date     2019/07/28
    * @author   zcx
    * @param    attrkey:属性对应的key
    * @return   无
    */
    void sendAttrChanged(QString attrkey);

    /**
    * @fn       setSelected(bool selected);
    * @brief    设置选中
    * @date     2019/07/17
    * @author   zcx
    * @param    selected:是否选中
    * @return   无
    */
    void setSelected(bool selected);

protected:
    /**
    * @fn       Asynchronous(const QVariant &pData);
    * @brief    子类实现，根据upDateData函数的第二次参数，选择是否异步处理函数
    *           此函数会自动调用，在子类中实现自己的异步（或者同步）操作，
    *           会在处理数据后，会刷新图元（一般用来实现自己类数据设定、数据处理）
    * @date     2019/07/08
    * @author   zcx
    * @param    pData:设置的数据
    * @return   是否异步成功
    */
    virtual bool Asynchronous(QVariant &pData);

    /**
    * @fn       load( QString fileName);
    * @brief    异步加载配置文件
    * @date     2019/07/08
    * @author   zcx
    * @param    fileName:配置文件名
    * @return   是否加载成功
    */
    virtual bool load( QString fileName);

    /**
    * @fn       attrUpdate(const QVariantMap &pDate);
    * @brief    更新属性,设置属性的时候会调用的函数
    * @date     2019/07/20
    * @author   zcx
    * @param    pDate:属性信息
    * @return   无
    */
    virtual void attrUpdate(const QVariantMap &pDate);


    /**
    * @fn       getAttrUpdate(QVariantMap &pDate);
    * @brief    得到属性的时候要调用的函数
    * @date     2019/07/20
    * @author   zcx
    * @param    无
    * @return   无
    */
    virtual void getAttrUpdate(QVariantMap &pDate);

    /**
    * @fn       SelectdChanged(bool selected);
    * @brief    选择改变
    * @date     2019/08/07
    * @author   zcx
    * @param    selected:是否选中
    * @return   无
    */
    virtual void SelectdChanged(bool selected);

    virtual void asynFinish();

    /**
    * @fn       isContainClickPos(QPointF pos);
    * @brief    是否包含的点(请在在调用items()后使用)
    * @author	zcx
    * @date     2019/12/19
    * @param	pos:点击的坐标(在场景中的)
    * @return	包含点击的点
    */
    virtual bool isContainPos(QPointF pos);

    /**
     * @brief 发射自定义属性
     * @param id:标识
     * @param data:数据
     */
    void SendCustomAttr(const QString &id,const QVariant &data);

signals:
    //发送数据处理完信号
    void sig_AsynFinish();

    //属性改变
    void sig_AttrChanged(const QString &id,const QString &attrKey);

    //自定义属性改变
    void sig_SendCustomAttr(const QString &id,const QVariant &data);

private slots:
    //数据处理完槽,用来刷新图元
    void slot_AsynFinish();

    void slot_EnabledChanged()   ;
    void slot_OpacityChanged()   ;
    void slot_ParentChanged()    ;
    void slot_RotationChanged()  ;
    void slot_ScaleChanged()     ;
    void slot_VisibleChanged()   ;
    void slot_XChanged()         ;
    void slot_YChanged()         ;
    void slot_ZChanged()         ;

private:
    //异步处理函数
    void AsynchronousFun(QVariant &pData);

    //更新属性
    void upDateAttr(const QVariantMap &pDate);

    //连接信号和槽
    void ConnectSig(const bool &state);

protected:
    QVariant                m_UpDateData;           //更新数据
    QVariantMap             m_Attrs;                //属性
    QRectF                  m_BoundRect;            //范围
    QString                 m_EventId;              //事件的标识
    QString                 m_ItemType;             //图元的类型
    QBrush                  m_Brush;                //当前的画刷
    QPen                    m_Pen;                  //当前的画笔
    qint64                  m_Order;                //添加的顺序
    CZDRAW::EditStatus      m_Edit;                 //是否编辑
    Qt::MouseButtons        m_MouseButtons;         //图元接受的鼠标事件
    static qint64           m_LastOrder;            //最后的序列
};

#endif // CZBASE_H
