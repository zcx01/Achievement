#ifndef CDRAGBUTTOM_H
#define CDRAGBUTTOM_H
/*******************************************************
    created     :   2019/08/21
    file base	:   CDragButton.h
    author      :   zcx
    purpose     :	测试拖拽
*******************************************************/\
#include <QPushButton>
#include <QVariantMap>

class CDragButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CDragButton(QWidget *parent = nullptr);

    virtual void sendDataFinished();

    void setDropData(const QVariantMap &data);

signals:

    void sig_Drag();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);

    void dragMoveEvent(QDragMoveEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:

    //拖放操作
    void performDrag();

    QPoint                      m_StartPos;                 //拖动开始的点
    QVariantMap                 m_Attrs;
};

#endif // CDRAGBUTTOM_H
