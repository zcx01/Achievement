#ifndef BROKENLINETOOL_H
#define BROKENLINETOOL_H

#include "CZBaseTool.h"

class BrokenLineTool : public CZBaseTool
{
    Q_OBJECT
public:
    explicit BrokenLineTool();

public:
	virtual QString getClassName();
	virtual void upDataTool(CZBase *item);
	virtual void addItem(CZBase *item);

private:
	bool isExitst(QString startId, QString endId);

	QPointF getItemCenterPoint(int heightScale,CZBase *item, QList<CZBase*> attachmentItems);

	struct BrokenLineInfo
	{
		QString startId;
		QString endId;
		QGraphicsPathItem*  path;
		BrokenLineInfo()
		{
			path = NULL;
		}

		bool isExist(QString start, QString end)
		{
			if (startId == start && endId == end)
			{
				return true;
			}
			return false;
		}
	};

	QList<BrokenLineInfo>  m_Infos;
};

#endif // BROKENLINETOOL_H