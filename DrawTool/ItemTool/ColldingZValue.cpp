#include "ColldingZValue.h"
ColldingZValue::ColldingZValue(QObject *parent) : CZBaseTool(parent)
{

}

ColldingZValue::~ColldingZValue()
{

}


QString ColldingZValue::getClassName()
{
    return "ColldingZValue";
}

void ColldingZValue::upDataTool(CZBase *item)
{
}

QVariant ColldingZValue::dealData(CZBase *item, void *pData)
{
    QList<QGraphicsItem *> items = item->collidingItems();
    if(!items.isEmpty())
    {
        std::sort(items.begin(),items.end(),ColldingZValue::CompareZValue);
        QGraphicsItem * maxZItem = items.last();
        int maxZValue = maxZItem->zValue();
        item->setZValue(++maxZValue);
        return maxZValue;
    }
    return QVariant();
}

bool ColldingZValue::CompareZValue(QGraphicsItem *f, QGraphicsItem *t)
{
    if(f->zValue() < t->zValue())
         return true;
    return false;
}
MYREGISTER(ColldingZValue)
