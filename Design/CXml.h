#ifndef CXML_H
#define CXML_H

#include "zxml_global.h"
#include <QObject>
#include <QVariantMap>
#include <QSharedPointer>
#include <QUuid>
typedef struct tag_XmlAttr                         //树状节点的结构体
{
    tag_XmlAttr             *parent;                 //父结构体
    QList<tag_XmlAttr *>    childs;                 //孩子集合
    QVariantMap             attrs;                  //节点信息
    QString                 tagName;                //节点的名字，只能是英文，中文写的时候没有问题，读取的时候有问题,不设置默认为node
    QString                 content;                //内容（只对末节点有效）
    QString                 comment;                //注释
    QString                 UUid;                   //Uid;唯一
    tag_XmlAttr()
    {
        parent = NULL;
        UUid = QUuid::createUuid().toString();
    }
    ~tag_XmlAttr()
    {
        for(int i =0; i< childs.size(); i++)
        {
            delete childs.at(i);
        }
    }

    void setParentFilgAttr(tag_XmlAttr *parentAttr)
    {
        if(parentAttr == NULL)
        {
            if(parent != NULL)
                parent->childs.removeOne(this);
            parent = NULL;
        }
        else
        {
            parent = parentAttr;
            parent->childs.push_back(this);
        }
    }

}XmlAttr,*tXmlAttr;
/*******************************************************
    created		:	2018/7/25
    file base	:	cxml.h
    author		:	zcx
    purpose		:	把结构体tagTreeAttr中的数据记录在xml中
                    也能把xml中的数据读取出来
*******************************************************/

class QDomDocument;
class QDomElement;
class QXmlStreamWriter;

typedef QSharedPointer<XmlAttr> XmlAtrrPtr;

class  ZXML_EXPORT CXml :public QObject
{
    Q_OBJECT
public:
    CXml();
    ~CXml();

    /**
        * @fn		writeNewXmlConfigFile(QString &fileName,QList<XmlAtrrPtr> filghtAttrs,QString rootName = "xmlConfig");
        * @brief    记录树中的数据，自动写入根节点
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName：文件名 filghtAttrs：数据集合 rootName：根节点
        * @return	是否写入成功
    */
    static bool writeNewXmlConfigFile(QString &fileName,QList<XmlAtrrPtr> filghtAttrs,QString rootName = "xmlConfig");



    /**
        * @fn		writeNewXmlConfigFile(QString &fileName,QList<XmlAtrrPtr> filghtAttrs,QString rootName = "xmlConfig");
        * @brief    记录树中的数据,包括根节点
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName：文件名 filghtAttrs：数据集合
        * @return	是否写入成功
    */
    static bool writeXmlConfigFile(QString &fileName,XmlAtrrPtr filghtAttr);

    /**
        * @fn		readNewXmlConfigFile(QString &fileName)const
        * @brief    读取树配置文件，没有储存根节点
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName:文件名
        * @return	数据集合
    */
    static QList<XmlAtrrPtr> readNewXmlConfigFile(QString &fileName);

    /**
        * @fn		readNewXmlConfigFile(QString &fileName)const
        * @brief    读取树配置文件,支持根节点
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName:文件名
        * @return	数据集合
    */
    static XmlAtrrPtr readXmlConfigFile(QString &fileName);

    /**
        * @fn		getAllTagTreeAttr(QList<XmlAtrrPtr> attrs);
        * @brief	去掉父子关系
        * @author	zcx
        * @date     2018/10/13
        * @param    attrs:数据集合
        * @return   数据
    */
    static QList<XmlAtrrPtr> getAllTagTreeAttr(QList<XmlAtrrPtr> attrs);

    /**
        * @fn		getXmlAttrPtrByUid(QList<XmlAtrrPtr> xmlAtrrs, QString Uid);
        * @brief	通过Uid得到XmlAtrrPtr
        * @author	zcx
        * @date		2018/10/13
        * @param	xmlAtrrs：数据集合 Uid:唯一标识符
        * @return   数据
    */
    static XmlAtrrPtr getXmlAttrPtrByUid(QList<XmlAtrrPtr> xmlAtrrs, QString Uid);

private:
    //重载函数，写一个孩子节点xml配置文件
    static void writeXmlChildConfigFile(XmlAttr *attr, QXmlStreamWriter &xmlStream);

    //从xml配置文件中读一个孩子节点
    static void readXmlChildConfigFile(QDomElement &parentElement, XmlAttr *parentAttr);

    //把QList转成QString，以","分割
    QString QListToQString(QList<QString> attr);

    //把bool转成QString
    QString boolToQString(bool checked);

    //把QString转成bool
    bool QStringTobool(QString str);

    //把数据写入xml中
    static void writeData(XmlAttr *attr, QXmlStreamWriter &xmlStream);

    //把xml中的数据存放在结构体中
    static void readData(QDomElement &element, XmlAttr *attr);


    //把数据写入xml中
    static void childTagTreeAttr(QList<XmlAtrrPtr> &attrs, XmlAttr *parentAttrs);
};

#endif // CXML_H
