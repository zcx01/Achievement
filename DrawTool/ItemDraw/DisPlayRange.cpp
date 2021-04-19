#include "DisPlayRange.h"

DisPlayRange::DisPlayRange()
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);
}

QString DisPlayRange::getClassName()
{
    return "DisPlayRange";
}

void DisPlayRange::attrUpdate(const QVariantMap &pDate)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);
}

MYREGISTER(DisPlayRange)
