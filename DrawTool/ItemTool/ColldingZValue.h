#ifndef COLLDINGZVALUE_H
#define COLLDINGZVALUE_H
/*******************************************************
    created		:	2019/12/21
    file base   :	ColldingZValue.h
    author		:	zcx
    purpose		:	顶置
*******************************************************/
#include "../BaseDraw/CZBaseTool.h"
class ColldingZValue : public CZBaseTool
{
    Q_OBJECT
public:
    explicit ColldingZValue(QObject *parent = 0);
    ~ColldingZValue();

    // CZBaseTool interface
public:
    QString getClassName();
    void upDataTool(CZBase *item);
    QVariant dealData(CZBase *item, void *pData);

    static bool CompareZValue(QGraphicsItem *f,QGraphicsItem *t);
};

#endif // COLLDINGZVALUE_H
