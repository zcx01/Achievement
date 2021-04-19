#include "BrokenLineTool.h"
#include "CManagementItem.h"
#include "hfdefine.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "CZStaticFun.h"
#include "ZXml/CXml.h"
//#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include "../DrawToolInclude/itemtooldefine.h"

BrokenLineTool::BrokenLineTool()
{

}

QString BrokenLineTool::getClassName()
{
	return "BrokenLineTool";
}

void BrokenLineTool::addItem(CZBase *item)
{
	upDataTool(item);
}


bool BrokenLineTool::isExitst(QString startId, QString endId)
{
	foreach(BrokenLineInfo info, m_Infos)
	{
		if (info.isExist(startId, endId))
		{
			return true;
		}
	}
	return false;
}

QPointF BrokenLineTool::getItemCenterPoint(int heightScale, CZBase *item, QList<CZBase*> attachmentItems)
{
 	if (!item || attachmentItems.isEmpty()) 
	{
		return QPointF();
	}

	double x = item->getThis()->pos().x() + item->boundingRect().width() / 2;

	double attachmentItemY = attachmentItems.at(0)->getThis()->pos().y();
	double itemY = item->getThis()->pos().y() + item->boundingRect().height();
	double y = itemY - (itemY - attachmentItemY) / heightScale;
	QPointF point;
	point.setX(x);
	point.setY(y);
	return point;
}

void BrokenLineTool::upDataTool(CZBase *item)
{
	D_ISNULLR(item, );
	QVariantMap attrs = item->getAttrs();
	QString idList = attrs.value(CHILDID).toString();
	int heightScale = attrs.value(HEIGHTSCALE).toInt();
	if (idList.isEmpty())
	{
		return;
	}
	QList<CZBase* > baseItems;
	QStringList attachmentIds = idList.split(",");
	for (int i = 0; i < attachmentIds.size(); i++)
	{
		if (isExitst(item->getId(), attachmentIds.at(i))) break;
		QString attachmentId = attachmentIds.at(i);
		if (!attachmentId.isEmpty())
		{
			CZBase* attachmentItem = getItemById(attachmentId);
			if (!attachmentItem)
			{
				break;
			}
			baseItems.append(attachmentItem);
		}
	}
	QPointF centerP = getItemCenterPoint(heightScale,item, baseItems);
	for (int i = 0; i < baseItems.size(); i++)
	{
		CZBase* attachmentItem = baseItems.at(i);
		D_ISNULLR(attachmentItem, );
		D_ISNULLR(item->scene(), );

		QPainterPath path;
		path.moveTo(centerP.x(), item->getThis()->pos().y() + item->boundingRect().height());
		path.lineTo(centerP.x(), item->getThis()->pos().y() + item->boundingRect().height());
		path.lineTo(centerP);
		path.lineTo(attachmentItem->getThis()->pos().x() + attachmentItem->boundingRect().width() / 2, centerP.y());
		path.lineTo(attachmentItem->getThis()->pos().x() + attachmentItem->boundingRect().width() / 2, attachmentItem->getThis()->pos().y());
		QGraphicsPathItem *pathItem = item->scene()->addPath(path);
		pathItem->setPen(CZStaticFun::QStringToQPen(attrs.value("Pen").toString()));
		pathItem->stackBefore(item);//item在lineLine前面
		pathItem->stackBefore(attachmentItem);
		BrokenLineInfo info;
		info.startId = item->getId();
		info.endId = attachmentItem->getId();
		info.path = pathItem;
		m_Infos.push_back(info);
	}
}
MYREGISTER(BrokenLineTool)
