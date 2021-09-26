#include "MainNavigationWidget.h"
#include "ui_MainNavigationWidget.h"
#include <QPushButton>
#include <QUuid>
#include <QTreeWidgetItem>
#include "TriangleWidget.h"
#include "GLSL.h"
#include "ETexture.h"
#include "Trans.h"
#include "Coordinate.h"
#include "Cude.h"
#include "CameraWidget.h"
#include "Lighting/Colors.h"
#include "Lighting/light2.h"
#include "Lighting/light3.h"
#include "Lighting/light4.h"
#include "Lighting/light5.h"
#include "Lighting/light6.h"
#include "Lighting/light7.h"
#include "Lighting/light8.h"
#include "AssimpModel/AssimpModel.h"
#include "HighOPenGL/TemplateTest.h"
#include "HighOPenGL/Blending.h"
#include "HighOPenGL/Blending2.h"
#include "HighOPenGL/FaceCulling.h"
#include "HighOPenGL/FrameTexture.h"
#include "HighOPenGL/Skybox.h"
#include "HighOPenGL/EnvironmentMapping.h"
#include "HighOPenGL/UniformBuffer.h"
#include "HighOPenGL/Geometry.h"
#include "HighOPenGL/Instantiation.h"
#include "HighOPenGL/instantiationarray.h"
#include "HighOPenGL/Planet.h"
#include "HighOPenGL/MSAA.h"
#include "HighLight/BlinnPhong.h"


#define UID Qt::UserRole+1
MainNavigationWidget::MainNavigationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainNavigationWidget)
{
    ui->setupUi(this);
    initWidget();
    ui->treeWidget->header()->hide();
    setWindowTitle("主窗体");
}


void MainNavigationWidget::initWidget()
{
    AddWidget(new TriangleWidget,"你好,三角形!");
    AddWidget(new GLSL,"着色器");
    AddWidget(new ETexture,"纹理");
    AddWidget(new Trans,"变换");
    AddWidget(new Coordinate,"坐标");
    AddWidget(new Cude,"立方体");
    AddWidget(new CameraWidget,"摄像机");
    QTreeWidgetItem* lightParentItem = AddWidget(NULL,"光照");
    AddWidget(new Colors,"颜色",lightParentItem);
    AddWidget(new light2,"基础光照",lightParentItem);
    AddWidget(new light3,"材质",lightParentItem);
    AddWidget(new light4,"光照贴图",lightParentItem);
    AddWidget(new light5,"定向光",lightParentItem);
    AddWidget(new light6,"点光源",lightParentItem);
    AddWidget(new light7,"聚光",lightParentItem);
    AddWidget(new light8,"多光源",lightParentItem);
    AddWidget(new AssimpModel,"加载模型");
    AddWidget(new TemplateTest,"模板测试(物体轮廓)");
    QTreeWidgetItem* BlendParentItem = AddWidget(NULL,"混合");
    AddWidget(new Blending,"草",BlendParentItem);
    AddWidget(new Blending2,"玻璃",BlendParentItem);
    AddWidget(new FaceCulling,"面剔除");
    QTreeWidgetItem* frameParentItem = AddWidget(NULL,"帧缓冲");
    AddWidget(new FrameTexture(":/config/HighOPenGL/frametexture/fragmentscreen.glsl"),"把所有场景的渲染到一个纹理上",frameParentItem);
    AddWidget(new FrameTexture(":/config/HighOPenGL/frametexture/fragmentsopposition.glsl"),"后期处理-反相",frameParentItem);
    AddWidget(new FrameTexture(":/config/HighOPenGL/frametexture/fragmentgrayscale.glsl"),"后期处理-灰度",frameParentItem);
    AddWidget(new FrameTexture(":/config/HighOPenGL/frametexture/fragmentkernel.glsl"),"后期处理-核效果",frameParentItem);
    AddWidget(new FrameTexture(":/config/HighOPenGL/frametexture/fragmentBlur.glsl"),"后期处理-模糊",frameParentItem);
    AddWidget(new FrameTexture(":/config/HighOPenGL/frametexture/fragmentedge-detection.glsl"),"后期处理-边缘检测",frameParentItem);

    QTreeWidgetItem* cudeParentItem = AddWidget(NULL,"立方体");
    AddWidget(new Skybox,"天空盒",cudeParentItem);
    AddWidget(new EnvironmentMapping("./config/HighOPenGL/skybox/cude_reflect_fragment.glsl"),"环境映射",cudeParentItem);
    AddWidget(new EnvironmentMapping("./config/HighOPenGL/skybox/cude_refract_fragment.glsl"),"环境折射",cudeParentItem);


    AddWidget(new UniformBuffer,"Uniform缓冲");
    AddWidget(new Geometry,"几何着色器");
    QTreeWidgetItem* instantiationItem = AddWidget(NULL,"大量实例渲染");
    AddWidget(new Instantiation,"实例化",instantiationItem);
    AddWidget(new InstantiationArray,"实例化数组",instantiationItem);
    AddWidget(new Planet,"小行星带",instantiationItem);

    AddWidget(new MSAA,"抗锯齿");
    AddWidget(new BlinnPhong,"高级光照");
}


MainNavigationWidget::~MainNavigationWidget()
{
    delete ui;
}

QTreeWidgetItem* MainNavigationWidget::AddWidget(QWindow *w, const QString &name, QTreeWidgetItem *parentItem, const int &index)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
//    button->setMinimumHeight(45);
//    item->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    item->setText(0,name);
    QString id = QUuid::createUuid().toString();
    item->setData(0,UID,id);
    if(parentItem == NULL)
    {
          ui->treeWidget->addTopLevelItem(item);
    }
    if(w != NULL)
    {
        QWidget * widget = QWidget::createWindowContainer(w);
        ui->stackedWidget->insertWidget(index,widget);
        m_AllWidgets.insert(id,widget);
    }
    return item;
}


void MainNavigationWidget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainNavigationWidget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(!item) return;
    QWidget *w = m_AllWidgets.value(item->data(0,UID).toString());
    if(!w) return;
    ui->stackedWidget->setCurrentWidget(w);
    setWindowTitle(item->text(column));
}
