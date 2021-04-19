#include "AlignmentTool.h"
#include <QDebug>
#include "../BaseDraw/CZStaticFun.h"
#include "../BaseDraw/CManagementItem.h"
#include "../DrawToolInclude/commdefine.h"

AlignmentTool::AlignmentTool(QObject *parent) : CZBaseTool(parent)
{

}

QString AlignmentTool::getClassName()
{
    return "AlignmentTool";
}

void AlignmentTool::upDataTool(CZBase *item)
{

}

QVariant AlignmentTool::dealData(CZBase *item, void *pData)
{
    QString type =* static_cast<QString *>(pData);
    Alignment(item,(AlignmentTypes)CZStaticFun::getEnums<AlignmentTool>(CS(AlignmentType),type,HorizontalAlignment),-1);
}

void AlignmentTool::Alignment(CZBase *reference, AlignmentTypes type, double distance)
{
    /**
     * 求参照的reference
     * 没有设置则为当前Item
     * 不是选择中为selectItem最后一个
     * */
    if(!reference) reference = m_ManagmentItem->getCurrent();
    QList<CZBase *> selectItems = m_ManagmentItem->getSelects();
    if(!reference || selectItems.contains(reference))
    {
        reference = selectItems.value(selectItems.size()-1);
    }
    if(!reference) return;

    /**
      *求距离
      * 没有设置为最远距离
      **/

    if(type & HorizontalEquidistant )
    {
        std::sort(selectItems.begin(),selectItems.end(),ItemCompX);
        if(distance == -1)
        {
            QList<QRectF> rects = getBoundRects(selectItems);
            for(int i =0;  i < rects.size() -1; i++)
            {
                distance = qMax(distance,calQRectMixH(rects.at(i),rects.at(i+1)));
            }
            for(int i=1; i < selectItems.size(); i++)
            {
                CZBase* bItem =selectItems.at(i);
                CZBase* item = selectItems.at(i-1);
                bItem->setX(item->x()+item->boundingRect().width()+distance);
            }
        }
    }

    if(type & VerticalEquidistant )
    {
        std::sort(selectItems.begin(),selectItems.end(),ItemCompY);
        if(distance == -1)
        {
            QList<QRectF> rects = getBoundRects(selectItems);
            for(int i =0;  i < rects.size() -1; i++)
            {
                distance = qMax(distance,calQRectMixV(rects.at(i),rects.at(i+1)));
            }
            for(int i=1; i < selectItems.size(); i++)
            {
                CZBase* bItem =selectItems.at(i);
                CZBase* item = selectItems.at(i-1);
                bItem->setY(item->y()+item->boundingRect().height()+distance);
            }
        }
    }

    foreach (CZBase *item, selectItems)
    {
        if(item != reference)
        {
            if(type & HorizontalAlignment)
            {
                qreal y = reference->y();
                qreal allY = reference->boundingRect().height() -item->boundingRect().height();
                if(type & Center)
                {
                    y += allY/2;
                }
                if(type & RightOrDowm)
                {
                    y += allY;
                }
                item->setY(y);
            }
            if(type & VerticalAlignment)
            {
                qreal x = reference->x();
                qreal allX = reference->boundingRect().width() -item->boundingRect().width();
                if(type & Center)
                {
                    x += allX/2;
                }
                if(type & RightOrDowm)
                {
                    x += allX;
                }
                item->setX(x);
            }
        }
    }

}

QList<QRectF> AlignmentTool::getBoundRects(QList<CZBase *> items)
{
    QList<QRectF> rects;
    foreach (CZBase *item, items)
    {
        QRectF boundRect = item->boundingRect();
        boundRect.translate(item->pos());
        rects<<boundRect;
    }
    return rects;
}

double AlignmentTool::calQRectMixH(const QRectF &f,const QRectF &t)
{
    return qMin(calQRectMinDistance(f.x(),f.width(),t.x()),
                calQRectMinDistance(t.x(),t.width(),f.x()));
}

double AlignmentTool::calQRectMixV(const QRectF &f, const QRectF &t)
{
    return qMin(calQRectMinDistance(f.y(),f.height(),t.y()),
                calQRectMinDistance(t.y(),t.height(),f.y()));
}

double AlignmentTool::calQRectMinDistance(const double &f, const double &d, const double &t)
{
    return t > f + d/2 ? t - (f +d ) : f - t;
}

bool AlignmentTool::QRectCompX(const QRectF &f, const QRectF &t)
{
    return f.x() < t.x();
}

bool AlignmentTool::QRectCompY(const QRectF &f, const QRectF &t)
{
    return f.y() < t.y();
}

bool AlignmentTool::ItemCompX(const CZBase *f, const CZBase *t)
{
    return /*!f || !t ? false :*/ f->x() < t->x();
}

bool AlignmentTool::ItemCompY(const CZBase *f, const CZBase *t)
{
    return !f || !t ? false : f->y() < t->y();
}
MYREGISTER(AlignmentTool)
