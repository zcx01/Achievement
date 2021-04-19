#ifndef BOUNDCHANGED_H
#define BOUNDCHANGED_H

/*******************************************************
    created		:	2019/12/21
    file base   :	BoundChanged.h
    author		:	zcx
    purpose		:	通过鼠标改变item的大小,
                    并且可以使用键盘移动图元(必须设置|QGraphicsItem::ItemIsFocusable)
*******************************************************/
#include "../BaseDraw/CZBaseTool.h"

class BoundChanged : public CZBaseTool
{
    Q_OBJECT
public:
    explicit BoundChanged(QObject *parent = 0);

    // CZBaseTool interface
    QString getClassName();
    void upDataTool(CZBase *item);
    void initTool();
    void removeItem(CZBase *item);

    enum ShowAssistType
    {
        VFAssist=0x01,//第一条垂直
        HTAssist=0x02,//第二条水平
        VTAssist=0x04,//第二条垂直
        HFAssist=0x08,//第一条水平
        VVAssist=VFAssist|VTAssist,
        HHAssist=HFAssist|HTAssist,
        VHAssist = VFAssist|HTAssist,
    };

    Q_DECLARE_FLAGS(ShowAssistTypes,ShowAssistType)

signals:

public slots:
    // CZBaseTool interface
protected:
    bool viewMouseMoveEvent(QMouseEvent *event);
    bool itemMousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    bool itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    bool itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    bool itemKeyPressEvent(QKeyEvent *event, QGraphicsItem *sourceItem);
    bool itemKeyReleaseEvent(QKeyEvent *event, QGraphicsItem *sourceItem);
    bool itemFocusOutEvent(QFocusEvent *event, QGraphicsItem *sourceItem);
private:
    enum CursorCtrlStyle      //鼠标的样式
    {
        CursorNormal = 0,        // 普通鼠标
        CursorTop,               //上
        CursorDowm,              //下
        Cursorleft,              //左
        CursorRight,             //右
        CursorHorVerleftTop,     // 水平和垂直拉伸  (从左上角开始)
        CursorHorVerleftDow,     // 水平和垂直拉伸  (从左下角开始)
        CursorHorVerRightDown,   // 水平和垂直拉伸  (从右下角开始)
        CurSorHorVerRightTop     // 水平和垂直拉伸  (从右上角开始)
    };

    //设置鼠标的样式
    void setCursorStyle(const QPointF &curPoint, CZBase *item);

    //计算大小
    void castSize(CursorCtrlStyle cursorStyle,const QPointF &curPoint,CZBase *item);

    //展示辅助线
    void ShowAssistLine(qreal pos1, qreal pos2, ShowAssistTypes type, qreal w, qreal h, CZBase *item);

    //隐藏辅助线
    void HideAssistLine();

    //辅助线改变
    void AssistLineChanged(CZBase* assistLine, QPointF pos, int type);

    void moveItem(QGraphicsItem *item, QPointF pos);

    bool                m_IsMousePress;
    CursorCtrlStyle     m_CurrentStyle;
    CZBase*             m_fAssistLine;          //第一条辅助线 0
    CZBase*             m_TAssistLine;          //第二条辅助线 1
    bool                m_ControlModifier;      //Ctrl是否按下
};
Q_DECLARE_OPERATORS_FOR_FLAGS(BoundChanged::ShowAssistTypes)
#endif // BOUNDCHANGED_H
