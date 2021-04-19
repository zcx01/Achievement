#ifndef COMPUTEGEOMETRY_H_
#define COMPUTEGEOMETRY_H_

/*******************************************************
    created		:	2019/12/19
    file base   :	ComputeGeometry.h
    author		:	zcx
    purpose		:	几何计算
*******************************************************/
#include <QPointF>
#include "cdraw_global.h"

class CDRAW_EXPORT ComputeGeometry
{
public:
    ComputeGeometry();
    virtual ~ComputeGeometry();
	
    /**
    * @fn       ComputeTouchPt(QPointF Center, double fRadius, QPointF LineBngPt, QPointF& lTouchPt, QPointF& rTouchPt);
    * @brief    计算圆的切点
    * @author	zcx
    * @date     2019/12/19
    * @param	Center - 圆心; fRadius - 半径; LineBngPt - 两条切线的共点
    * @return	lTouchPt - 左切点; rTouchPt - 右切点
    */
    static bool ComputeTouchPt(QPointF Center, double fRadius, QPointF LineBngPt, QPointF& lTouchPt, QPointF& rTouchPt);

    /**
    * @fn       IsLeft(QPointF PO, QPointF P1, QPointF P2);
    * @brief    判断一条线段是否在另一条线段的左侧
    * @author	zcx
    * @date     2019/12/19
    * @param	P0:点0 P1:点1 P2:点2
    * @return	否在另一条线段的左侧
    */
    static bool	IsLeft(QPointF PO, QPointF P1, QPointF P2);
	
    /**
    * @fn       ComputeCirAndLine(bool bClocked, QPointF BgnPt, QPointF Center, bool bFirset,
                                  double fRadius, QPointF TargetPt,double& Angle, QPointF& TouchPt);
    * @brief    计算切线
    * @author	zcx
    * @date     2019/12/19
    * @param	bClocked - 是否顺时针; BgnPt - 起始点; Center - 圆心; fRadius - 半径; TargetPt - 目标点
                bFirst: true - 取从BgnPt开始顺时针或逆时针（由bClocked确定）的第一个点; false - 第二个点
    * @return	Angle - 弧度; TouchPt - 切点
    */
    static bool ComputeCirAndLine(bool bClocked, QPointF BgnPt, QPointF Center, bool bFirset,
                                  double fRadius, QPointF TargetPt,double& Angle, QPointF& TouchPt);
    /**
    * @fn       GetLineDistance(QPointF bgnPt, QPointF endPt);
    * @brief    获取两点距离
    * @author	zcx
    * @date     2019/12/19
    * @param	bgnPt:开始点 endPt:结束点
    * @return	距离
    */
    static double GetLineDistance(QPointF bgnPt, QPointF endPt);
    static double CalcDisByPoints(double fBgnX, double fBgnY, double fEndX, double fEndY);

    /**
    * @fn       DistancePointToLine(QPointF a, QPointF b, QPointF c, QPointF& droopPt, bool& isDroop);
    * @brief    获取点到直线的距离
    * @author	zcx
    * @date     2019/12/19
    * @param	a,b 是线段两端点 c是线段外的一点 isDroop用来判定垂足是否落在线段上
    * @return	直线的距离 droopPt:垂直的点
    */
    static double DistancePointToLine(QPointF a, QPointF b, QPointF c, QPointF& droopPt, bool& isDroop);
	
    /**
    * @fn       GetLineAngle(QPointF bgnPt, QPointF endPt);
    * @brief    通过两点计算两点组成直线的偏角弧度，弧度是相对数学坐标系的值
    * @author	zcx
    * @date     2019/12/19
    * @param	bgnPt:开始点 endPt:结束点
    * @return	直线的偏角弧度
    */
    static double	GetLineAngle(QPointF bgnPt, QPointF endPt);
	static double	GetLineAngle(double fBgnX, double fBgnY, double fEndX, double fEndY);

    /**
    * @fn       QPointF ComputeCirPointByPoint(QPointF cirCenterCoor,
                                          QPointF cirCoor, double fCirRad,
                                          double fArcAngle, double& fAngled);
    * @brief    给定圆心，圆上一点和一偏角弧度，得出圆上另一点，及这两点的方向角
    * @author	zcx
    * @date     2019/12/19
    * @param	cirCenterCoor:圆心 cirCoor:圆上一点 fCirRad:半径 fArcAngle:一偏角弧度
    * @return	圆上另一点 fAngled:这两点的方向角
    */
    static QPointF ComputeCirPointByPoint(QPointF cirCenterCoor,
                                          QPointF cirCoor, double fCirRad,
                                          double fArcAngle, double& fAngled);
	
    /**
    * @fn       GetAngle(QPointF o, QPointF s, QPointF e);
    * @brief    求两线段的夹角, 顺时针
    * @author	zcx
    * @date     2019/12/19
    * @param	o:顶点 s:起点 e:终点;
    * @return   夹角
    */
    static double GetAngle(QPointF o, QPointF s, QPointF e);
    static double getAngle( QPointF o, QPointF s, QPointF e );

    /**
    * @fn       pointByDistance(QPointF oriPoint, double distance, int angle = 0);
    * @brief    计算终点坐标(以中心为坐标原点)
    * @date     2019/05/12
    * @author   zcx
    * @param    oriPoint:起始点 distance:距离 angle:角度
    * @return   终点坐标
    */
    static QPointF pointByDistance(QPointF oriPoint, double distance, int angle = 0);

};

#endif //COMPUTEGEOMETRY_H_
