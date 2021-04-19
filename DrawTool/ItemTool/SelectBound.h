#ifndef SELECTBOUND_H
#define SELECTBOUND_H
/*******************************************************
    purpose     :	选中图元，边框变色
*******************************************************/
#include "../BaseDraw/CZBaseTool.h"
#include <QGraphicsRectItem>

class SelectBound : public CZBaseTool
{
    Q_OBJECT
public:
    SelectBound();

    // CZBaseTool interface
public:
    QString getClassName();
    void upDataTool(CZBase *item);
    void initTool();
    void removeItem(CZBase *item);

private slots:
    void slot_SelectChanged();

private:
    void addSelect(CZBase *item);

    void removeSelect(CZBase * item);

    QHash<CZBase*, QGraphicsItem*>  m_Rects;
};

#endif // SELECTBOUND_H
