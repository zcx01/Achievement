#ifndef ATTACHMENT_H
#define ATTACHMENT_H

/*******************************************************
    created     :   2019/07/28
    file base	:   Attachment.h
    author      :   zcx
    purpose     :	连线功能
*******************************************************/
#include "CZBaseTool.h"
#include <QRectF>

class Attachment : public CZBaseTool
{
    Q_OBJECT
public:
    explicit Attachment(QObject *parent = nullptr);

    // CZBaseTool interface
    virtual QString getClassName();
    virtual void upDataTool(CZBase *item);

protected:
    // CZBaseTool interface
    virtual void addItem(CZBase *item);
    virtual void removeItem(CZBase *item);
    //virtual bool itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
signals:

public slots:

    void slot_LineChanged();

private:

    bool isExitst(QString startId,QString endId);

    bool lineChanged(CZBase *item);

    struct Info
    {
        QString startId;
        QString endId;
        QGraphicsLineItem*  line;
        Info()
        {
            line = NULL;
        }

        bool isExist(QString start,QString end)
        {
            if(startId == start && endId == end)
            {
                return true;
            }
            return false;
        }
    };

    QList<Info>  m_Infos;
};

#endif // ATTACHMENT_H
