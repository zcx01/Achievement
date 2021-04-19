#include "FlowTextGrid.h"
#include "DrawToolInclude/zattrdefine.h"
#include "../BaseDraw/CZStaticFun.h"
#include "../BaseDraw/ComputeGeometry.h"
#include "../BaseDraw/czdrawstruct.h"
#include "DrawToolInclude/commdefine.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>


FlowTextGrid::FlowTextGrid()
{
    m_CellSize = QSize(20,60);
    m_DisPlayRange = new DisPlayRange;
    m_DisPlayRange->setParentItem(this);
}

QString FlowTextGrid::getClassName()
{
    return "FlowTextGrid";
}

void FlowTextGrid::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF ori(0,0);
    QRectF tableRect(ori.x(),ori.y(),m_CellSize.width(), m_CellSize.height() * m_Platforms.size());  //所有文字的大小
    int textWidth = tableRect.width();  //平台文字的宽度

    //画流程的名字
    if(!m_FlowName.isEmpty())
    {
        painter->drawText(tableRect,Qt::AlignCenter,m_FlowName);
        painter->drawLine(tableRect.topRight(),tableRect.bottomRight());
        ori += QPoint(tableRect.width(),0);
    }
    else
    {
        textWidth *= 2;
    }
    tableRect.setWidth(tableRect.width() * 2 );
    //画框
    painter->drawRect(tableRect);

    m_TextRectFs.clear();
    for(int i =0 ; i < m_Platforms.size() ; i++)
    {
        QPointF drowMove =QPoint(0, m_CellSize.height() * (i+1));

        //平台文字
        QPointF pS = ori + drowMove;
        QPointF pE = pS + QPointF(textWidth,0);

        //文字下方的线
        painter->drawLine(pS,pE);
        QRectF pTextRect = QRectF(pS-QPoint(0,m_CellSize.height()),pE);
        painter->drawText(pTextRect,Qt::AlignCenter,m_Platforms.at(i));
        m_TextRectFs.insert(m_Platforms.at(i),pTextRect);

        //画网格
        QPointF gE =boundingRect().topRight().toPoint() + drowMove;
        painter->drawLine(pE,gE);
    }
}

void FlowTextGrid::AddScene(QGraphicsScene *s)
{
    UpdataSize();
}

void FlowTextGrid::attrUpdate(const QVariantMap &pDate)
{
    m_CellSize = CZStaticFun::QStringToQSizeF(pDate.value(D_CellSize).toString(),m_CellSize);
    m_Platforms = pDate.value(D_Platforms).toString().split(SJOIN);
    m_FlowName = pDate.value(D_FlowText).toString();
    setData(BACKGOUNDINDEX,true);
    m_DisPlayRange->setData(BACKGOUNDINDEX,true);
    setFlags(flags() | QGraphicsItem::ItemClipsChildrenToShape);
    UpdataSize();
}

bool FlowTextGrid::Asynchronous(QVariant &pData)
{
    QVariantMap attr = pData.toMap();
    int type = attr.value(F_GetPosType).toInt();
    switch (type) {
    case Dr::GridHeight:
    {
        int index = m_Platforms.indexOf(attr.value(F_PlatformName).toString());
        double y = GetHeightByIndex(index);
        double h = m_CellSize.height() * 0.8;
        QPointF pos = mapToScene(QPointF(0,y - h / 2));//移到中间
        attr.insert(F_NodeH,h);
        attr.insert(F_NodeY,pos.y());
    }
        break;
    case Dr::SetParentItem:
    {
        CZBase * item = attr.value(F_NodeParent).value<CZBase *>();
        if(item)
        {
            item->setParentItem(m_DisPlayRange);
        }
    }
        break;
    default:
        break;
    }
    pData.setValue(attr);
    return true;
}

void FlowTextGrid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CZBase::mousePressEvent(event);
    for(auto iter = m_TextRectFs.begin(); iter != m_TextRectFs.end(); iter++)
    {
        if(iter.value().contains(event->pos()))
        {
            qDebug()<<iter.key()<<"点击了";
            sendAttrChanged(iter.key());
        }
    }
}

void FlowTextGrid::UpdataSize()
{
    if(scene())
    {
        double x = boundingRect().x();
        double y = boundingRect().y();
        double w = scene()->sceneRect().width();
        double h = GetHeight();
        setBounding(QRectF(x,y,w,h));

        //设置范围
        //int count = m_FlowName.isEmpty() ? 1 : 2;
        double dis =  m_CellSize.width() * 2;
        m_DisPlayRange->setPos(dis,0);
        m_DisPlayRange->setBounding(QRectF(0,0,w - dis,h));
    }
}

double FlowTextGrid::GetHeight()
{
    return m_CellSize.height() * m_Platforms.size();
}

double FlowTextGrid::GetHeightByIndex(int index)
{
    return m_CellSize.height() * (index + 0.5);
}

MYREGISTER(FlowTextGrid)
