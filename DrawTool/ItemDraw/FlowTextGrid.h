#ifndef FLOWTEXTGRID_H
#define FLOWTEXTGRID_H
/*******************************************************
    purpose     :	流程显示文本网格
*******************************************************/
#include "../BaseDraw/CZBase.h"
#include "DisPlayRange.h"

class FlowTextGrid :public CZBase
{
    Q_OBJECT
public:
    FlowTextGrid();

    // CZBase interface
    QString getClassName();
    void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void AddScene(QGraphicsScene *s);

    // CZBase interface
protected:
    void attrUpdate(const QVariantMap &pDate);
    bool Asynchronous(QVariant &pData);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:

    //更新大小
    void UpdataSize();

    //得到高度
    double GetHeight();

    //通过索引得到高度
    double GetHeightByIndex(int index);

    QSize                   m_CellSize;     //单个表格的大小
    QString                 m_FlowName;     //流程名
    QList<QString>          m_Platforms;    //平台名
    DisPlayRange*           m_DisPlayRange; //范围
    QHash<QString,QRectF>   m_TextRectFs;   //文本矩形的范围
};

#endif // FLOWTEXTGRID_H
