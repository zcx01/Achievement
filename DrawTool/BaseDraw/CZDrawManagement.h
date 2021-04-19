#ifndef CZDRAWMANAGEMENT_H
#define CZDRAWMANAGEMENT_H
/*******************************************************
    created     :   2019//
    file base	:
    author      :   zcx
    purpose     :

工具的xml结构：
    toolClassName为工具的类名，fileName:工具的配置文件
    <root>
        <toolClassName>fileName</toolClassName>
    </root>

item的拥有工具的xml结构:
    itemClassName:为item的类名，（唯一）
    toolClassNames:工具类型组合(用“,”隔开),toolClassNames是属性节点不可变
    <root>
        <itemClassName toolClassNames="toolClassName1,toolClassName2,..."></itemClassName>
    </root>

item关系
    <root>
        <toolClassName>
        </toolClassName>
    </root>
*******************************************************/
#include <QObject>
#include "czdrawstruct.h"
#include "cdraw_global.h"
class CManagementTool;
class CManagementItem;
class QGraphicsScene;
class CZBase;
typedef struct tag_XmlAttr XmlAttr;
class CDRAW_EXPORT CZDrawManagement : public QObject
{
    Q_OBJECT
public:
    explicit CZDrawManagement(QWidget *parent = nullptr);
    ~CZDrawManagement();

    //------------------------------file(文件)---------------------------
    /**
    * @fn       loadTool(QString fileName);
    * @brief    加载工具
    * @date     2019/07/18
    * @author   zcx
    * @param    fileName:工具的配置文件
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
    * @date     2019/07/18
    * @author   zcx
    * @param    fileName:配置item的文件
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
    * @fn       loadFileName(QString fileName);
    * @brief    加载配置文件
    * @date     2019/07/20
    * @author   zcx
    * @param    fileName:文件名 先加入工具，在是初始化使用工具
    * @return   是否成功
    */
    bool loadItemFileName(QString fileName);

    /**
    * @fn       saveItemFile(QString fileName);
    * @brief    保存item的属性到配置文件
    * @author	zcx
    * @date     2019/12/21
    * @param	fileName:文件名
    * @return	是否成功
    */
    bool saveItemFile(QString fileName);

    //------------------------------item（图元）---------------------------
    /**
    * @fn       createItem(QString className,const QVariantHash &attr);
    * @brief    创建一个绘图的item(如果有父类，父类必须先创建)
    * @date     2019/07/18
    * @author   zcx
    * @param    className:类名,attr:属性
    * @return   item的标识
    */
    QString createItem(QString className, const QVariantMap &attr);


    /**
    * @fn       createItemByType(const QString &itemType);
    * @brief    通过类型创建一个item
    * @date     2019/08/03
    * @author   zcx
    * @param    itemType:item的类型
    * @return   item的标识
    */
    QString createItemByType(const QString &itemType);

    /**
    * @fn       deleteItem(QString id);
    * @brief    删除item
    * @date     2019/07/18
    * @author   zcx
    * @param    id:标识
    * @return   是否删除成功
    */
    bool deleteItem(QString id);

    /**
    * @fn       clearAllItem(const bool &clearBackgound = true);
    * @brief    清除所有的图元
    * @date     2019/07/30
    * @author   zcx
    * @param    clearBackgound:是否清除背景
    * @return   无
    */
    void clearAllItem(const bool &clearBackgound = true);

    /**
    * @fn       setCurrentId(const QString &id);
    * @brief    设置当前图元
    * @date     2019/07/25
    * @author   zcx
    * @param    id:图元的标识
    * @return   无
    */
    void setCurrentId(const QString &id);

    /**
    * @fn       getCurrentId();
    * @brief    得到当前item的id
    * @date     2019/07/29
    * @author   zcx
    * @param    无
    * @return   当前item的id
    */
    QString getCurrentId();

    /**
    * @fn       getSelects();
    * @brief    得到选中的Id
    * @date     2019/07/29
    * @author   zcx
    * @param    无
    * @return   选中的Id
    */
    QList<QString> getSelects();


    /**
    * @fn       setEdit(const CZDRAW::EditStatus &state,QString id = QString(""));
    * @brief    设置图元的编辑状态
    * @date     2019/07/25
    * @author   zcx
    * @param    state:编辑 id:标识(空的值当前的id)
    * @return   是否成功
    */
    bool setEdit(const CZDRAW::EditStatus &state,QString id = QString(""));

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
    * @fn       getKeyType(const QString &id,const QString &key);
    * @brief    得到一个键值的类型
    * @author	zcx
    * @date     2019/12/20
    * @param	id:标识 key:键值
    * @return	类型
    */
    QVariant::Type getKeyType(const QString &id,const QString &key);

    //------------------------------itemAttr(图元属性)---------------------------
    /**
    * @fn       upDateItemAttr(DrawItemAttrPtr ptr);
    * @brief    更新Item的属性信息（id = className,则指的是更新工具）
    * @date     2019/07/18
    * @author   zcx
    * @param    ptr:信息
    * @return   是否更新成功
    */
    bool upDateItemAttr(DrawItemAttrPtr ptr);

    /**
    * @fn       getItemAttr(QString id);
    * @brief    得到item的属性信息（如果id是类名，返回是工具的信息）
    * @date     2019/07/18
    * @author   zcx
    * @param    id:item的标识（或者工具的类名）
    * @return   item的信息（工具的信息）
    */
    DrawItemAttrPtr getItemAttr(QString id);

    /**
    * @fn       getCurrentAttr();
    * @brief    得到当前的item的属性
    * @date     2019/07/18
    * @author   zcx
    * @param    无
    * @return   item的信息
    */
    DrawItemAttrPtr getCurrentAttr();

    /**
    * @fn       getAttrByItemType(const QString &itemType);
    * @brief    通过类型得到属性
    * @date     2019/08/01
    * @author   zcx
    * @param    无
    * @return   属性
    */
    QVariantMap getAttrByItemType(const QString &itemType);

    //------------------------------View(视图)---------------------------
    /**
    * @fn       setVisible(const bool &state);
    * @brief    设置显隐
    * @date     2019/07/18
    * @author   zcx
    * @param    state:是否显示
    * @return   无
    */
    void setVisible(const bool &state);

    /**
    * @fn       getVisible() const;
    * @brief    得到是否显示
    * @date     2019/07/18
    * @author   zcx
    * @param    无
    * @return   是否显示
    */
    bool getVisible() const;

    /**
    * @fn       setViewAttr(const QVariantMap &attr);
    * @brief    设置视图的属性
    * @date     2019/07/31
    * @author   zcx
    * @param    attr:视图的属性
    * @return   无
    */
    void setViewAttr(const QVariantMap &attr);

    /**
    * @fn       getViewAttr();
    * @brief    得到视图的属性
    * @date     2019/07/31
    * @author   zcx
    * @param    无
    * @return   视图的属性
    */
    QVariantMap getViewAttr();

    /**
    * @fn       getWidget();
    * @brief    得到显示的窗体
    * @date     2019/07/28
    * @author   zcx
    * @param    无
    * @return   显示的窗体
    */
    QWidget* getWidget();


    /**
     * @brief 缩放的增量
     * @param delta:缩放的增量
     */
    void setZoomDelta(qreal delta);

    /**
     * @brief 放大
     */
    void ZoomIn();

    /**
     * @brief 缩小
     */
    void ZoomOut();

    /**
     * @brief 缩放，scaleFactor倍数
     * @param scaleFactor:倍数
     */
    void Zoom(float scaleFactor);

    /**
     * @brief 还原
     */
    void Restore();

    /**
     * @brief 得到场景
     */
    QGraphicsScene* GetScene();

    //------------------------------Tool(工具)---------------------------
    /**
    * @fn       upDateToolData(QString id,QString toolClassName,void* pData);
    * @brief    更新工具中的数据(无视是否该id标识的图元是否属于toolClassName工具)、处理大数据使用
    * @date     2019/07/18
    * @author   zcx
    * @param    id:item的标识 toolClassName:工具的名字 pData:数据
    * @return   处理后的结果
    */
    QVariant upDateToolData(QString id,QString toolClassName,void* pData);

    /**
     * @fn      ToolDealData
     * @brief   工具处理数据(无视是否该id标识的图元是否属于toolClassName工具)、处理比较小的数据使用
     * @date    2020/5/20
     * @param   id:item的标识 toolClassName:工具的名字 pData:数据
     * @return  处理后的结果
     */
    QVariant ToolDealData(QString id,QString toolClassName,const QVariant &pData);

    /**
    * @fn       upDateTool(const QString toolClassName,const QString &id);
    * @brief    更新指定工具
    * @date     2019/07/26
    * @author   zcx
    * @param    toolClassName:工具的类名 id:item的标识
    * @return   无
    */
    void upDateTool(const QString toolClassName,const QString &id);

    /**
    * @fn       upDateClassTool(const QString &className);
    * @brief    一个item对应的所有工具
    * @date     2019/07/26
    * @author   zcx
    * @param    id:item的标识
    * @return   无
    */
    void upDateItemAllTool(const QString &id);

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
    * @fn       setCurrentToolActiva(QString toolClassName, bool state);
    * @brief    主动的设置活跃的工具
    * @author	zcx
    * @date     2019/12/12
    * @param	toolClassName:工具的类名 state:是否活跃
    * @return	无
    */
    void setCurrentToolActiva(QString toolClassName, bool state);

    /**
    * @fn       addItemToTool(const QString &itemType,const QString &toolClassName);
    * @brief    添加item到指定的工具中,添加加失败有std::logic_error异常抛出
    * @author	zcx
    * @date     2019/12/21
    * @param    itemType:图元的类型 toolClassName:工具的类名
    * @return   无
    */
    void addItemToTool(const QString &itemType,const QString &toolClassName);

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
     * @brief item添加完成
     * @param toolClassName:类名
     */
    void itemAddFinishToTool(const QString &toolClassName);
signals:
    //属性改变的属性
    void sig_AttrChanged(QString id,QString key);

    //选择改变
    void sig_SelectChanged();

    //当前选择改变
    void sig_CurrentChanged(QString  oldId,QString currentId);

    //创建完成
    void sig_CreateFinish(QString id);

    //发射自定义属性
    void sig_SendCustomAttr(QString id,QVariant data);

public slots:
    //当前选择改变
    void slot_CurrentChanged(CZBase*  old,CZBase* current);

    //属性改变的槽
    void slot_AttrChanged(QString id,QString key);

    //创建item
    void slot_CreateItem(QVariantMap attr);
private:
    //通过item的指针得到相关信息
    DrawItemAttrPtr getItemAttrByHand(CZBase *item);

    //创建子item
    void createChildItem(CZBase *parentItem, XmlAttr *parentAttr);

    //比较item创建顺序
    static bool CompOrder(CZBase *f,CZBase *t);

    CManagementTool*    m_ManagmentTool;
    CManagementItem*    m_ManagmentItem;
    QGraphicsScene*     m_Scene;             //Scene

};

#endif // CZDRAWMANAGEMENT_H
