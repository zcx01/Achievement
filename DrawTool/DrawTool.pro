TEMPLATE = subdirs

SUBDIRS += \
    BaseDraw/BaseDraw.pro\             #绘图的基础类
    DrawToolPublic/DrawToolPublic.pro\ #公用的类
    #DrawToolWidget/DrawToolWidget.pro\ #流程图使用
    ItemTool/ItemTool.pro\             #工具类
    ItemDraw/ItemDraw.pro\             #绘图类
    DrawWidget/DrawWidget.pro\
    chart/chart.pro
	
CONFIG += ordered
