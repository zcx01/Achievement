#include "ComputeGeometry.h"
#define DPI	3.1415926535898

ComputeGeometry::ComputeGeometry()
{

}

ComputeGeometry::~ComputeGeometry()
{

}

bool ComputeGeometry::ComputeTouchPt(QPointF Center, double fRadius, QPointF LineBngPt, QPointF& lTouchPt, QPointF& rTouchPt )
{
    double fDist = GetLineDistance(Center, LineBngPt);								//圆心与目标点的距离，公里
    if(fDist <= fRadius || fDist <= 1.f || fRadius <= 0.5f)														//距离过小
    {
        return false;
    }

    //	double angle1;
    QPointF TouchPt1;
    QPointF TouchPt2;

    double fSin1 = (Center.ry() - LineBngPt.ry()) / fDist;
    double fCos1 = (Center.rx() - LineBngPt.rx()) / fDist;
    double fSin2 = fRadius / fDist;										//该角度一定是锐角
    double fCos2 = sqrt(1 - fSin2 * fSin2);

    TouchPt1.setX(Center.rx() - fRadius * (fSin2 * fCos1 + fCos2 * fSin1));
    TouchPt1.setY(Center.ry() + fRadius * (fCos2 * fCos1 - fSin2 * fSin1));

    TouchPt2.setX(Center.rx() + fRadius * (fSin1 * fCos2 - fCos1 * fSin2));
    TouchPt2.setY(Center.ry() - fRadius * (fCos1 * fCos2 + fSin1 * fSin2));

    if (IsLeft(LineBngPt, Center, TouchPt1))
    {
        lTouchPt = TouchPt1;
        rTouchPt = TouchPt2;
    }
    else
    {
        lTouchPt = TouchPt2;
        rTouchPt = TouchPt1;
    }

    return true;
}

/*******************************************************************************************************
功能描述    : 判断一条线段是否在另一条线段的左侧
            若(p2 - p0) × (p1 - p0) > 0,则p0p1在p1点拐向右侧后得到p1p2
若(p2 - p0) × (p1 - p0) < 0,则p0p1在p1点拐向左侧后得到p1p2
若(p2 - p0) × (p1 - p0) = 0,则p0、p1、p2三点共线
********************************************************************************************************/
bool ComputeGeometry::IsLeft( QPointF PO, QPointF P1, QPointF P2 )
{
    QPointF P2MP0;										//p2 - p0
    QPointF P1MP0;										//p1 - p0

    P2MP0.setX(P2.rx() - PO.rx());							//p2 - p0
    P2MP0.setY(P2.ry() - PO.ry());

    P1MP0.setX(P1.rx() - PO.rx());							//p1 - p0
    P1MP0.setY(P1.ry() - PO.ry());

    return (P2MP0.rx() * P1MP0.ry() - P1MP0.rx() * P2MP0.ry() < 0);
}

bool ComputeGeometry::ComputeCirAndLine( bool bClocked, QPointF BgnPt, QPointF Center, bool bFirset,
                                         double fRadius, QPointF TargetPt,double& Angle, QPointF& TouchPt )
{
    double fDist = GetLineDistance(Center, TargetPt);								//圆心与目标点的距离，公里
    if(fDist <= fRadius || fDist <= 1.f || fRadius <= 0.5f)														//距离过小
    {
        return false;
    }

    //	double angle1;
    QPointF TouchPt1;
    QPointF TouchPt2;

    double fSin1 = (Center.ry() - TargetPt.ry()) / fDist;
    double fCos1 = (Center.rx() - TargetPt.rx()) / fDist;
    double fSin2 = fRadius / fDist;										//该角度一定是锐角
    double fCos2 = sqrt(1 - fSin2 * fSin2);

    TouchPt1.setX(Center.rx() - fRadius * (fSin2 * fCos1 + fCos2 * fSin1));
    TouchPt1.setY(Center.ry() + fRadius * (fCos2 * fCos1 - fSin2 * fSin1));

    TouchPt2.setX(Center.rx() + fRadius * (fSin1 * fCos2 - fCos1 * fSin2));
    TouchPt2.setY(Center.ry() - fRadius * (fCos1 * fCos2 + fSin1 * fSin2));

    if(bClocked)
    {
        if (IsLeft(BgnPt,TouchPt1,TouchPt2))
        {
            TouchPt	= TouchPt2;
            Angle	= GetAngle(Center,BgnPt,TouchPt2);
        }
        else
        {
            TouchPt	= TouchPt1;
            Angle	= GetAngle(Center,BgnPt,TouchPt1);
        }
    }

    return true;
}

double ComputeGeometry::GetLineDistance( QPointF bgnPt, QPointF endPt )
{
    return sqrt((double)((endPt.ry() - bgnPt.ry()) * (endPt.ry() - bgnPt.ry())) + (double)((endPt.rx() - bgnPt.rx()) * (endPt.rx() - bgnPt.rx())));
}

double ComputeGeometry::CalcDisByPoints( double fBgnX, double fBgnY, double fEndX, double fEndY )
{
    return sqrt((double)((fEndY - fBgnY) * (fEndY - fBgnY) + (double)(fEndX - fBgnX) * (fEndX - fBgnX)));
}

double ComputeGeometry::DistancePointToLine( QPointF a, QPointF b, QPointF c, QPointF& droopPt, bool& isDroop )
{
    QPointF ab = b - a;
    QPointF ac = c - a;

    float f = ab.rx() * ac.rx() + ab.ry() * ac.ry();
    if (f < 0)
    {
        isDroop = false;				//并非垂线
        droopPt = a;
        return GetLineDistance(c,a);
    }

    float d = (ab.rx() * ab.rx()) + (ab.ry() * ab.ry());
    if (f > d)
    {
        isDroop = false;				//并非垂线
        droopPt = b;
        return GetLineDistance(c,b);
    }

    f /= d;
    droopPt = a + f * ab;
    isDroop = true;						//是垂线段的长度
    return GetLineDistance(c,droopPt);
}

double ComputeGeometry::GetLineAngle(QPointF bgnPt,QPointF endPt )
{
    //计算起点角度
    double r	= sqrt((endPt.rx() - bgnPt.rx()) * (endPt.rx() - bgnPt.rx()) + (endPt.ry() - bgnPt.ry()) * (endPt.ry() - bgnPt.ry()));
    double arcsin;
    if(r == 0)
        arcsin = 0;
    else
        arcsin = (double)qAbs(endPt.ry() - bgnPt.ry()) / r;

    double startAngle = asin(arcsin) * 180 / DPI;						//计算出来的值在第一象限，范围为[0, 90]
    if (endPt.ry() - bgnPt.ry() > 0 && endPt.rx() - bgnPt.rx() < 0)		//在第二象限
    {
        startAngle = 180 - startAngle;
    }
    else if (endPt.ry() - bgnPt.ry() < 0 && endPt.rx() - bgnPt.rx() < 0)	//在第三象限
    {
        startAngle = startAngle + 180;
    }
    else if (endPt.ry() - bgnPt.ry() < 0 && endPt.rx() - bgnPt.rx() > 0)	//在第四象限
    {
        startAngle = 360 - startAngle;
    }
    else if (endPt.ry() - bgnPt.ry() == 0 && endPt.rx() - bgnPt.rx() < 0)	 //在x负半轴上
    {
        startAngle = 180;
    }
    else if (endPt.rx() - bgnPt.rx() == 0 && endPt.ry() - bgnPt.ry() > 0)	 //在Y在正半轴上
    {
        startAngle = 90;
    }
    else if (endPt.rx() - bgnPt.rx() == 0 && endPt.ry() - bgnPt.ry() < 0) //在Y的负半轴上
    {
        startAngle = 270;
    }

    return startAngle * DPI / 180;
}

double ComputeGeometry::GetLineAngle( double fBgnX, double fBgnY, double fEndX, double fEndY )
{
    QPointF bgnPt(fBgnX,fBgnY);
    QPointF endPt(fEndX,fEndY);
    return GetLineAngle(bgnPt, endPt);
}

QPointF ComputeGeometry::ComputeCirPointByPoint( QPointF cirCenterCoor,
                                                 QPointF cirCoor, double fCirRad,
                                                 double fArcAngle, double& fAngled )
{
    QPointF unKnownCoor;
    double fArc = GetLineAngle(cirCenterCoor, cirCoor);
    fArc += fArcAngle;

    unKnownCoor.setX(cos(fArc) * fCirRad + cirCenterCoor.rx());
    unKnownCoor.setY(sin(fArc) * fCirRad + cirCenterCoor.ry());

    fAngled = GetLineAngle(cirCoor, unKnownCoor);

    return unKnownCoor;
}

double ComputeGeometry::GetAngle( QPointF o, QPointF s, QPointF e )
{
    double cosfi,fi,norm;
    double dsx = s.rx() - o.rx();
    double dsy = s.ry() - o.ry();
    double dex = e.rx() - o.rx();
    double dey = e.ry() - o.ry();

    cosfi=dsx*dex+dsy*dey;
    norm=(dsx*dsx+dsy*dsy)*(dex*dex+dey*dey);
    cosfi /= sqrt( norm );

    if (cosfi >= 1.0 ) return 0;
    if (cosfi <= -1.0 ) return DPI;

    fi=acos(cosfi);
    if (dsx*dey-dsy*dex<0) return fi; // 说明矢量os在矢量oe的逆时针方向
    return (-fi+DPI*2);
}



double ComputeGeometry::getAngle( QPointF o, QPointF s, QPointF e )
{
    double cosfi,fi,norm;
    double dsx = s.rx() - o.rx();
    double dsy = s.ry() - o.ry();
    double dex = e.rx() - o.rx();
    double dey = e.ry() - o.ry();

    cosfi=dsx*dex+dsy*dey;
    norm=(dsx*dsx+dsy*dsy)*(dex*dex+dey*dey);
    cosfi /= sqrt( norm );

    if (cosfi >= 1.0 ) return 0;
    if (cosfi <= -1.0 ) return DPI;

    fi=acos(cosfi);
    if (dsx*dey-dsy*dex<0) return fi;
    return (-fi+DPI*2);
}

QPointF ComputeGeometry::pointByDistance(QPointF oriPoint, double distance, int angle)
{
    double x1 = oriPoint.rx() + distance * cos(angle * DPI / 180);
    double y2 = oriPoint.ry() + distance * sin(angle * DPI / 180);
    QPointF rectF(x1,y2);
    return rectF;
}
