#include "DrawWidgetFactory.h"
#include "./HfFrameReflect/cmyregistersingle.h"
#include "./ZXml/CXml.h"
#include <QBoxLayout>
#include <QApplication>
#include "BaseDrawObject.h"
#include <QLibrary>

DrawWidgetFactory::DrawWidgetFactory(QWidget *parent)
    : QWidget(parent)
{
    QString configFilePath = QApplication::applicationDirPath()+"/DrawToolConfig/DrawWidgetConfig.xml";
    LoadConfig(configFilePath);
}

DrawWidgetFactory::~DrawWidgetFactory()
{
    qDeleteAll(m_Objs.values());
    m_Objs.clear();
}

bool DrawWidgetFactory::LoadConfig(QString configFilePath)
{
    XmlAtrrPtr ptr = CXml::readXmlConfigFile(configFilePath);
    if(ptr.isNull()) return false;
    QBoxLayout *layout = NULL;
    if(ptr->attrs.value("IsV").toBool())
    {
        layout = new QVBoxLayout(this);
    }
    else
    {
        layout = new QHBoxLayout(this);
    }

    QStringList dllNames = ptr->attrs.value("dllNames").toString().split(",");
    foreach (QString dllName, dllNames)
    {
        load(dllName);
    }

    layout->setMargin(0);
    layout->setSpacing(0);

    for(int i =0; i < ptr->childs.size(); i++)
    {
        XmlAttr* attr = ptr->childs.at(i);
        if(attr->attrs.value("IsShow",true).toBool())
        {
            BaseDrawObject * drawWidget = static_cast<BaseDrawObject *>
                    (CMyRegisterSingle::instance()->getClass(attr->attrs.value("ClassName").toString()));
            if(drawWidget)
            {
                QString drawConfigDirPath = attr->attrs.value("DrawConfigDirPath").toString();
                drawWidget->InitManagement(drawConfigDirPath,layout);
                m_Objs.insert(attr->UUid,drawWidget);
            }
        }
    }
    return true;
}

void DrawWidgetFactory::load(QString libName)
{
    QString dll;
    {

#ifdef QT_DEBUG
        {
#ifdef linux
            dll = QApplication::applicationDirPath()+QString("/lib%1d.so").arg(libName);
#else
            dll = QApplication::applicationDirPath()+QString("/%1d.dll").arg(libName);
#endif

        }
#else
        {
#ifdef linux
            dll = QApplication::applicationDirPath()+QString("/lib%1.so").arg(libName);
#else
            dll = QApplication::applicationDirPath()+QString("/%1.dll").arg(libName);
#endif
        }
#endif
        QLibrary lib(dll);
        if(!lib.isLoaded())
        {
            lib.load();
        }
    }
}

void DrawWidgetFactory::contextMenuEvent(QContextMenuEvent *event)
{
    foreach (BaseDrawObject *obj, m_Objs)
    {
        obj->contextMenuEvent(event);
    }
}
