#include "FoldLine.h"
#include "../BaseDraw/CZStaticFun.h"
#include "../BaseDraw/ComputeGeometry.h"
#include <QPainter>
#include "../DrawToolInclude/zattrdefine.h"
#include "../DrawToolInclude/commdefine.h"
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include "../BaseDraw/ComputeGeometry.h"

PointAttr::PointAttr()
{
    textWidth = 1;
    textItem = NULL;
    preAttr = NULL;
    textItemPos = Center;
}

PointAttr::~PointAttr()
{
    D_Delete(textItem);
}

void PointAttr::setPos(QPointF p)
{
    pos = p;
    setTextItemPos(p);
}

void PointAttr::setPreAttr(PointAttr *ptr)
{
    D_ISNULLR(ptr,);
    textBrush  =ptr->textBrush;
    textWidth  =ptr->textWidth;
    textColor  =ptr->textColor;
    textFont   =ptr->textFont;
    textItemPos=ptr->textItemPos;
    preAttr = ptr;
}

void PointAttr::setTextItemPos(QPointF p)
{
    D_ISNULLR(textItem,);
    switch (textItemPos)
    {
    case Border:
        textItem->setPos(p);
        break;
    case Center:
    {
        if(!preAttr)
        {
            D_Delete(textItem);
            return;
        }
        QLineF line(preAttr->pos,this->pos);
        //textItem->rotate(270-line.angle());
        QPointF ce = line.pointAt(0.5);
        textItem->setPos(QPointF(ce.x()-textItem->boundingRect().width()/2,
                                 ce.y()-textItem->boundingRect().height()/2));
    }
        break;
    default:
        break;
    }
}


//////////////////////////////////////////////////////////
#define ENLARGE 2
FoldLine::FoldLine(QGraphicsItem *parent) : CZBase(parent)
{
    m_Range = 20;
}

FoldLine::~FoldLine()
{
    m_PointAttrs.clear();
}


void FoldLine::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPath(m_Path);
    //处理节点
    QTransform trans = painter->transform();
    if(m_FoldNodePen != QPen())
    {
        painter->setPen(m_FoldNodePen);
    }
    if(m_FoldNodeBrush != QBrush())
    {
        painter->setBrush(m_FoldNodeBrush);
    }

    if(m_Attrs.value(SELECTED).toBool() && m_NodeStyle != NoNodeStyle)
    {
        //画圆
        int lastIndex = 0;
        m_ArrowsStyle & FoldLine::NoArrow ? lastIndex =0 : lastIndex =1;
        for(int i =0; i <m_PointAttrs.size()-lastIndex; i++)
        {
            PointAttrPtr pos = m_PointAttrs.at(i);
            //保持放大后不变
            if(trans.m11() && trans.m22())
            {
                QRectF rect(0,0,m_Range/trans.m11(),m_Range/trans.m22());
                rect.moveCenter(pos->pos);
                switch (m_NodeStyle) {
                case Ellipse:
                    painter->drawEllipse(rect);
                    break;
                case Rect:
                    painter->drawRect(rect);
                    break;
                default:
                    break;
                }
            }
        }
    }
    //画箭头
    if(m_PointAttrs.size() > 1 && !(m_ArrowsStyle & FoldLine::NoArrow))
    {
        PointAttrPtr sPos = m_PointAttrs.last();    //原点
        PointAttr* pPos =sPos->preAttr;  //上个点
        if(pPos && trans.m11() && trans.m22())
        {
            int angle =180- QLineF(sPos->pos,pPos->pos).angle();
            QPointF pos1 = ComputeGeometry::pointByDistance(sPos->pos,m_Range/trans.m11(),180-15+angle);
            QPointF pos2 = ComputeGeometry::pointByDistance(sPos->pos,m_Range/trans.m11(),180+15+angle);
            QPainterPath path;
            QPolygonF polygon;
            if(m_ArrowsStyle & FoldLine::SealTriangle || m_ArrowsStyle & FoldLine::NoSealTriangle)
            {
                polygon.append(pos1);
                polygon.append(sPos->pos);
                polygon.append(pos2);
            }
            if(m_ArrowsStyle & FoldLine::SealTriangle)
            {
                polygon.append(pos1);
            }
            path.addPolygon(polygon);
            painter->drawPath(path);
        }
    }
}

void FoldLine::keyPressEvent(QKeyEvent *event)
{
    CZBase::keyPressEvent(event);
}

QString FoldLine::getClassName()
{
    return "FoldLine";
}

QPainterPath FoldLine::shape() const
{

    return CZBase::shape();
}

void FoldLine::slot_EditFinsh(QGraphicsTextItem *item)
{
    foreach (PointAttrPtr ptr, m_PointAttrs)
    {
        if(ptr->textItem == item)
        {
            ptr->text = item->toPlainText();
            setTextItemAttr(ptr->textItem,ptr.data());
        }
    }
}

void FoldLine::createPointAttrPtr(PointAttr* attr,int index)
{
    D_ISNULLR(attr,);
    PointAttrPtr ptr(attr);
    if(index == -1)
    {
        if(!m_PointAttrs.isEmpty())
            attr->setPreAttr(m_PointAttrs.value(m_PointAttrs.size()-1).data());
        m_PointAttrs<<ptr;
    }
    else
    {
        //重新设置
        PointAttrPtr prePtr = m_PointAttrs.value(index-1);
        PointAttrPtr brePtr = m_PointAttrs.value(index);
        if(!brePtr.isNull())
        {
            brePtr->setPreAttr(ptr.data());
        }
        m_PointAttrs.insert(index,ptr);
        ptr->setPreAttr(prePtr.data());
    }
    if(!attr->text.isEmpty())
    {
        ZGraphicsTextItem *textItem = new ZGraphicsTextItem(getThis()->parentItem());
        attr->textItem = textItem;
        textItem->setParentItem(this);
        connect(textItem,SIGNAL(sig_EditFinsh(QGraphicsTextItem*)),this,
                SLOT(slot_EditFinsh(QGraphicsTextItem*)));

        setTextItemAttr(textItem,attr);
    }

}

void FoldLine::setTextItemAttr(ZGraphicsTextItem *textItem,PointAttr *attr)
{
    D_ISNULLR(attr,);
    D_ISNULLR(textItem,);
    textItem->document()->clear();
    QTextCharFormat charFormat;

    QBrush brush = attr->textBrush;
    if(brush.color().isValid())
        charFormat.setBackground(brush);
    charFormat.setFontWeight(attr->textWidth);
    charFormat.setForeground(attr->textColor);
    textItem->setFont(attr->textFont);
    textItem->textCursor().insertText(attr->text,charFormat);
    attr->setTextItemPos(attr->pos);//一定要放在最后,因为有可能把textItem删除
}

void FoldLine::attrUpdate(const QVariantMap &pDate)
{
    m_PointAttrs.clear();
    QStringList points =  pDate.value(FOLDPOINTS).toString().split(JOIN);
    QStringList texts  =  pDate.value(FOLDTEXTS).toString().split(JOIN);
    QStringList brushs =  pDate.value(FOLDTEXTBRUSH).toString().split(JOIN);
    QStringList widths =  pDate.value(FOLDTEXTWIDTH).toString().split(JOIN);
    QStringList colors =  pDate.value(FOLDTEXTCOLOR).toString().split(JOIN);
    QStringList fonts  =  pDate.value(FOLDTEXTFONT).toString().split(JOIN);
    QStringList itemPos=  pDate.value(FOLDTEXTITEMPOS).toString().split(JOIN);
    int index = 0;
    foreach (QString p, points)
    {
        if(!p.isEmpty())
        {
            PointAttr* attr = new PointAttr;
            attr->setPos(CZStaticFun::QStringToQPointF(p));
            attr->text = texts.value(index,attr->text);
            createPointAttrPtr(attr);
            if(!pDate.value(FOLDNOUSESAME).toBool() || index == 0)
            {
                if(!brushs.value(index).isEmpty())
                {
                    attr->textBrush = CZStaticFun::QStringToQBrush(brushs.at(index));
                }
                attr->textWidth =widths.value(index,QString::number(attr->textWidth)).toInt();
                if(!colors.value(index).isEmpty())
                {
                    attr->textColor = CZStaticFun::QStringToQColor(colors.at(index));
                }
                if(!fonts.value(index).isEmpty())
                {
                    attr->textFont =CZStaticFun::QStringToQFont(fonts.at(index));
                }
                attr->textItemPos =(PointAttr::TextItemPos)itemPos.
                        value(index,QString::number(attr->textItemPos)).toInt();

                setTextItemAttr(attr->textItem,attr);
            }
        }
        index++;
    }
    add();

    isAttrValueValid(FOLDPOINTRANGE) ? m_Range = m_Attrs.value(FOLDPOINTRANGE).toInt():m_Range;

    m_ArrowsStyle = CZStaticFun::getEnums<FoldLine>
            (CS(ArrowsStyle),m_Attrs.value(FOLDARROWSSTYLE).toString(),NoArrow);

    m_NodeStyle= CZStaticFun::getEnums<FoldLine>
            (CS(NodeStyle),m_Attrs.value(FOLDANODESTYLE).toString(),NoNodeStyle);

    QString penString = m_Attrs.value(FOLDNODEPEN).toString();
    m_FoldNodePen = CZStaticFun::QStringToQPen(penString);

    QString brushString = m_Attrs.value(FOLDNODEBRUSH).toString();
    m_FoldNodeBrush = CZStaticFun::QStringToQBrush(brushString);

    UpDateBound();
}

void FoldLine::saveToAttr(bool NoUseSame)
{
    QStringList points;
    QStringList texts  ;
    QStringList brushs ;
    QStringList widths ;
    QStringList colors ;
    QStringList fonts  ;
    QStringList itemPos;
    for(int i =0; i < m_PointAttrs.size(); i++)
    {
        PointAttrPtr ptr = m_PointAttrs.at(i);
        points<<CZStaticFun::QPointFTOQString(ptr->pos);
        texts<<ptr->text;
        if(!NoUseSame && i !=0)
        {
            continue;
        }
        brushs<<CZStaticFun::QBrushToQString(ptr->textBrush);
        widths<<QString::number(ptr->textWidth);
        colors<<CZStaticFun::QColorToQString(ptr->textColor);
        fonts<<CZStaticFun::QFontToQString(ptr->textFont);
        itemPos<<QString::number(ptr->textItemPos);
    }
    if(!m_PointAttrs.isEmpty())
    {
        m_Attrs.insert(FOLDPOINTS,points.join(JOIN));
        m_Attrs.insert(FOLDTEXTS,texts.join(JOIN));
        m_Attrs.insert(FOLDTEXTBRUSH,brushs.join(JOIN));
        m_Attrs.insert(FOLDTEXTWIDTH,widths.join(JOIN));
        m_Attrs.insert(FOLDTEXTCOLOR,colors.join(JOIN));
        m_Attrs.insert(FOLDTEXTFONT,fonts.join(JOIN));
        m_Attrs.insert(FOLDTEXTITEMPOS,itemPos.join(JOIN));
    }
}

void FoldLine::OnlySavePoint()
{
    QStringList points;
    for(int i =0; i < m_PointAttrs.size(); i++)
    {
        PointAttrPtr ptr = m_PointAttrs.at(i);
        points<<CZStaticFun::QPointFTOQString(ptr->pos);
    }
    if(!m_PointAttrs.isEmpty())
    {
        m_Attrs.insert(FOLDPOINTS,points.join(JOIN));
    }
}

int FoldLine::GetIndexByPoint(QPointF pos)
{
    int index =-1;
    for(int i =0; i < m_PointAttrs.size() ; i++)
    {
        QRectF rect(0,0,m_Range,m_Range);
        rect.moveCenter(getThis()->mapToScene(m_PointAttrs.at(i)->pos));
        if(rect.contains(pos))
        {
            index = i;
            break;
        }
    }
    return index;
}

void FoldLine::getAttrUpdate(QVariantMap &pDate)
{
    // m_Attrs.value()
}

void FoldLine::add()
{
    QPainterPath path;
    if(!m_PointAttrs.isEmpty())
    {
        path.moveTo(m_PointAttrs.first()->pos);
    }
    for(int i =1; i < m_PointAttrs.size(); i++)
    {
        QPointF pos = m_PointAttrs.at(i)->pos;
        if(!pos.isNull())
        {
            path.lineTo(pos);
        }
    }
    m_Path = path;
}

bool FoldLine::Asynchronous(QVariant &pData)
{
    QVariantMap tmpData = pData.toMap();
    int editStatus = tmpData.value(EDITSTATUS).toInt();
    //QPointF pos; //要操作的点
    switch (editStatus) {
    case Dr::NewBuild:
        add();
        break;
    case Dr::ADD:
    {
        int index = tmpData.value(FOLDCURINDEX).toInt();
        QPointF pos = tmpData.value(FOLDCURPOINT).toPointF();
        QString text = tmpData.value(FOLDCURTEXT).toString();
        addPoint(pos,text,index);
    }
        break;
    case Dr::Modify:
    {
        int index = tmpData.value(FOLDCURINDEX).toInt();
        QPointF newPos = tmpData.value(FOLDCURPOINT).toPointF();
        ModifyPointPos(index,newPos);
    }
        break;
    case Dr::Delete:
    {
        int index = tmpData.value(FOLDCURINDEX).toInt();
        DeletePoint(index);
    }
        break;
    case Dr::Save:
    {
        saveToAttr(m_Attrs.value(FOLDNOUSESAME).toBool());
    }
        break;
    case Dr::OnlySavePoint:
    {
        OnlySavePoint();
    }
        break;
    case Dr::GetCurrentIndex:
    {
        QPointF pos = tmpData.value(FOLDCURPOINT).toPointF();
        int index = GetIndexByPoint(pos);
        tmpData.insert(FOLDCURINDEX,index);
        pData.setValue(tmpData);
    }
        break;
    default:
        break;
    }
    UpDateBound();
    return true;
}

bool FoldLine::isContainPos(QPointF pos)
{
    bool isContain = false;
    QPointF sPos = getThis()->mapFromScene(pos);
    if(!m_PointAttrs.isEmpty())
    {
        if(m_PointAttrs.size() == 1)
        {
            isContain = contains(sPos);
        }
        else
        {
            int index =1;
            while(index < m_PointAttrs.size())
            {
                QPointF beg = m_PointAttrs.at(index)->preAttr->pos;
                QPointF end = m_PointAttrs.at(index)->pos;
                QPointF vPos;
                bool isDroop = false;
                int distance = ComputeGeometry::DistancePointToLine(beg,end,sPos,vPos,isDroop);
                if(distance < m_Range)
                {
                    isContain = true;
                    break;
                }
                index++;
            }
        }
    }
    return isContain;
}

void FoldLine::UpDateBound()
{
    QRectF rect = m_Path.controlPointRect();
    int enlarge = m_Range;
    QPointF cen = rect.center();
    rect.setSize(QSize(rect.width()+enlarge,rect.height()+enlarge));
    rect.moveCenter(cen);
    setBounding(rect);

    //    if(!pos.isNull())
    //    {
    //        QRectF updateRect(0,0,enlarge,enlarge);
    //        updateRect.moveCenter(pos);
    //        getThis()->scene()->update(updateRect);
    //    }
}

void FoldLine::addPoint(QPointF pos, const QString &text, int index)
{
    PointAttr* attr = new PointAttr;
    if(text.isEmpty())
        attr->text = m_Attrs.value(FOLDDEFAULT,true).toBool() ? QString::number(m_PointAttrs.size()) : "";
    else
        attr->text = text;
    attr->setPos(pos);
    createPointAttrPtr(attr,index);
    add();
}

QPointF FoldLine::ModifyPointPos(int index, QPointF newPos)
{
    QPointF pos;
    if(index >= 0 && index < m_Path.elementCount())
    {
        pos = m_PointAttrs.at(index)->pos;
        m_PointAttrs.at(index)->setPos(newPos);
        PointAttrPtr brePtr = m_PointAttrs.value(index+1);
        if(!brePtr.isNull() &&brePtr->textItemPos == PointAttr::Center)
        {
            m_PointAttrs.at(index+1)->setTextItemPos(QPointF());
        }
        m_Path.setElementPositionAt(index,newPos.x(),newPos.y());
    }
    return pos;
}

void FoldLine::DeletePoint(int index)
{
    PointAttrPtr prePtr = m_PointAttrs.value(index-1);
    PointAttrPtr brePtr = m_PointAttrs.value(index+1);
    if(!brePtr.isNull())
    {
        brePtr->setPreAttr(prePtr.data());
        if(brePtr->textItemPos == PointAttr::Center)
        {
            m_PointAttrs.at(index+1)->setTextItemPos(QPointF());
        }
    }
    m_PointAttrs.removeAt(index);
    add();
}

MYREGISTER(FoldLine)
