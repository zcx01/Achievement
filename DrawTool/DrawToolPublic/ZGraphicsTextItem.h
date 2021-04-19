#ifndef ZGRAPHICSTEXTITEM_H
#define ZGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QTextDocument>
#include "drawtoolpublic_global.h"

class DRAWTOOLPUBLIC_EXPORT ZGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit ZGraphicsTextItem(QGraphicsItem * parent = NULL);
    ~ZGraphicsTextItem();
signals:
    void sig_EditFinsh(QGraphicsTextItem *);

    // QGraphicsItem interface
protected:
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // ZGRAPHICSTEXTITEM_H
