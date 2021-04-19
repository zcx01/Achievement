#ifndef ADSORB_H
#define ADSORB_H

/*******************************************************
    created     :   2019/08/21
    file base	:   Adsorb.h
    author      :   zcx
    purpose     :	吸附
*******************************************************/
#include "CZBaseTool.h"
#include <QRectF>

class Adsorb : public CZBaseTool
{
public:
    Adsorb();

    // CZBaseTool interface
public:
    virtual QString getClassName();
    virtual void initTool();
    virtual void upDataTool(CZBase *item);

    // CZBaseTool interface
protected:
    virtual bool itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);

private:

    //计算吸附的点
    QRectF calcAdsorbPoint(CZBase *item);

    QList<QRectF>   m_RectF;

};

#endif // ADSORB_H
