#include "Adsorb.h"
#include "hfdefine.h"
#include "CZBase.h"
#include "CZStaticFun.h"
#include <QGraphicsScene>
#include "../DrawToolInclude/itemtooldefine.h"

Adsorb::Adsorb()
{

}


QString Adsorb::getClassName()
{
    return "Adsorb";
}

void Adsorb::initTool()
{
    CZBase *item = getItemById(ADSORBID);
    D_ISNULLR(item,);
    QString rects = item->getAttrs().value(ADSORBRECT).toString();
    QList<QString> stringRects = rects.split(";");
    foreach (QString stringRect, stringRects)
    {
        QRectF rect =CZStaticFun::QStringToQRectF(stringRect);
        m_RectF.push_back(rect);
        //item->scene()->addRect(rect);
    }
}


bool Adsorb::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    CZBase *item = dynamic_cast<CZBase*>(sourceItem);
    D_ISNULLR(item,false);
    if(item->getId() != ADSORBID)
    {
        QRectF tmpRect = calcAdsorbPoint(item);
        if(tmpRect.isNull()) return false;
//        QPointF cenPoint = CZStaticFun::castShowPoint(tmpRect,QRect(),4);
//        cenPoint+=tmpRect.topLeft();
//        cenPoint-=item->pos();
//        qDebug()<<cenPoint<<tmpRect.center();
//        qDebug()<<tmpRect.center()<<tmpRect.center()-item->boundingRect().center();
        item->setPos(tmpRect.center()-item->boundingRect().center());
 //       return true;
    }
    return false;
}

QRectF Adsorb::calcAdsorbPoint(CZBase *item)
{
    QRectF rectF;
    D_ISNULLR(item,rectF);
    CZBase *adsorbItem = getItemById(ADSORBID);
    D_ISNULLR(adsorbItem,rectF);

    //如果item的范围在某个矩形范围内，则返回该矩形的中心点
    QRectF itemBound = item->mapToScene(item->boundingRect()).boundingRect();
    foreach (QRectF rect, m_RectF)
    {
        if(rect.contains(itemBound))
        {
            return rect;
        }
    }

    //如果不在范围内则，求中心点与某一矩形的中心点最近
    QPointF f = itemBound.center();
    int index = 0;
    QLineF minLine;//短的线
    foreach (QRectF rect, m_RectF)
    {
        QPointF t = rect.center();
        if(index == 0)
        {
            minLine.setPoints(f,t);
            rectF = rect;
            index++;
            continue;
        }
        QLineF tmpLine(f,t);
        if(tmpLine.length() < minLine.length())//长度较短的线
        {
            rectF = rect;
            minLine = tmpLine;
        }
    }
    return rectF;
}

MYREGISTER(Adsorb)


void Adsorb::upDataTool(CZBase *item)
{
}
