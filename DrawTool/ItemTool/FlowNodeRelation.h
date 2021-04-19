#ifndef FLOWNODERELATION_H
#define FLOWNODERELATION_H
/*******************************************************
    purpose     :	流程节点关系
                    可以创建折线
*******************************************************/
#include "CZBaseTool.h"

class FlowNodeRelation : public CZBaseTool
{
    Q_OBJECT
public:
    FlowNodeRelation();

    // CZBaseTool interface
public:
    QString getClassName();
    void upDataTool(CZBase *item);
    void addItem(CZBase *item);
    void removeItem(CZBase *item);

    // CZBaseTool interface
protected:
    bool viewResizeEvent(QResizeEvent *event);

private slots:
    //时间刻度大小改变
    void slot_TimeShow(QString id,QString attr);

    //节点图元位置改变
    void slot_PosChanged(QString id,QString attr);
private:

    //初始化数据
    void initData();

    //计算图元的位置
    void CalItemPos(CZBase * item);

    //更新所有的item的位置
    void CalAllItemPos();

    //计算item的关系
    void CalItemRelation(CZBase * item);

    //发送折线的位置
    void SendFoldPos(const QPointF &pos, int index, CZBase *item,const bool &isAdd);

    //设置父图元
    void SetParentItem(CZBase *item, CZBase *grid);

    /**
     * @brief 坐标转化
     * @param item:参考坐标
     * @param pos:场景中的坐标
     * @return item父类的坐标
     */
    QPointF PosCover(CZBase *item,QPointF pos);

    //根据开始时间的大小，自动计算前一个节点
    void AutoCalPreNode(CZBase *item);

    //插入一个节点
    void InsertNode(CZBase *item);

    //插入一个节点
    void InsertNode(CZBase* preItem, CZBase* item, CZBase* nextItem);

    /**
     * @brief 判断折线是否在节点内
     * @param pos:折线父类的坐标
     * @param except:除外
     * @return 节点内
     */
    bool foldIsNodeIn(const QPointF &pos,CZBase *except);

    /**
     * @brief 节点上的点是否被使用
     * @param item:节点图元
     * @param pos:场景坐标
     * @return 使用
     */
    bool nodePosIsUse(CZBase *item,const QPointF &pos);

    //得到节点图元
    QList<CZBase *> GetNodeItems();

    //通过时间排序
    static bool ItemBySTime(CZBase *f,CZBase *t);

    CZBase*                                 m_TimeScale;        //时间刻度
    QHash<QString,CZBase*>                  m_Grids;            //网格
    QHash<CZBase*,CZBase *>                 m_RelationLines;    //key为后节点,关系线集
};

#endif // FLOWNODERELATION_H
