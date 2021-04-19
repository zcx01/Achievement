#ifndef ZATTRDEFINE_H
#define ZATTRDEFINE_H
/*******************************************************
    created     :   2019/08/08
    file base	:   zattrdefine.h
    author      :   zcx
    purpose     :   item属性宏定义
*******************************************************/

#define LINEPEN             "LinePen"

//CDrawImage
#define CURRENTINDEX        "currentIndex"      //当前显示的图片
#define IMAGEFILENAMES      "imageFilenames"    //图片的文件名集合

//CRotaryImage
#define IMAGE               "Image"             //默认的图片
#define SELECTIMAGE         "SelectImage"       //选中的图片
#define CLICKVISIBLE        "ClickVisible"      //点击的时候才会显示

//DrawSvg
#define SVGFILENAME         "SvgFileName"       //svg图片路径
#define SVGELEMENTID        "SvgeLementId"      //节点的ID

//FoldLine
#define FOLDTEXTS           "FoldTexts"         //文本集
#define FOLDTEXTBRUSH       "FoldTextBrush"     //文本的背景
#define FOLDTEXTWIDTH       "FoldTextWidth"     //文本的宽度
#define FOLDTEXTCOLOR       "FoldTextColor"     //文本的颜色
#define FOLDTEXTFONT        "FoldTextFont"      //文本的字体
#define FOLDTEXTITEMPOS     "FoldTextItemPos"   //文本的位置
#define FOLDNOUSESAME       "FoldNoUseSame"     //不使用同样文本样式(bool)
#define FOLDARROWSSTYLE     "FoldArrowsStyle"   //(QString)箭头的样式
#define FOLDANODESTYLE      "FoldNodeStyle"     //(QString)节点的样式
#define FOLDNODEPEN         "FoldNodePen"       //节点或者箭头的画笔
#define FOLDNODEBRUSH       "FoldNodeBrush"     //箭头的画刷

//AssistLine
#define LINEDIRECTION       "LineDirection"     //线的方向

//FlowTextGrid
#define D_Platforms         "Platforms"         //平台名称
#define D_FlowText          "FlowText"          //流程名称
#define D_CellSize          "CellSize"          //表格的大小

//TimeScale
#define D_STime             "STime"             //开始的时间
#define D_ETime             "ETime"             //结束的时间
#define D_LeftMargin        "LeftMargin"        //左边距
#define D_TextMargin        "TextMargin"        //文字边距

#define D_LeftTime          "LeftTime"          //左时间

//DSector

#define DS_Lenght          "Lenght"             //长度
#define DS_SAngle          "SAngle"             //开始的角度
#define DS_EAngle          "EAngle"             //结束的角度
#endif // ZATTRDEFINE_H
