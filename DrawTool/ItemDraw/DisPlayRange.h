#ifndef DISPLAYRANGE_H
#define DISPLAYRANGE_H

/*******************************************************
    purpose     :	显示的范围
*******************************************************/

#include "../BaseDraw/CZBase.h"
class DisPlayRange : public CZBase
{
public:
    DisPlayRange();

    // CZBase interface
public:
    QString getClassName();
    void attrUpdate(const QVariantMap &pDate);
};

#endif // DISPLAYRANGE_H
