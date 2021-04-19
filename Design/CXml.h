#ifndef CXML_H
#define CXML_H

#include "zxml_global.h"
#include <QObject>
#include <QVariantMap>
#include <QSharedPointer>
#include <QUuid>
typedef struct tag_XmlAttr                         //��״�ڵ�Ľṹ��
{
    tag_XmlAttr             *parent;                 //���ṹ��
    QList<tag_XmlAttr *>    childs;                 //���Ӽ���
    QVariantMap             attrs;                  //�ڵ���Ϣ
    QString                 tagName;                //�ڵ�����֣�ֻ����Ӣ�ģ�����д��ʱ��û�����⣬��ȡ��ʱ��������,������Ĭ��Ϊnode
    QString                 content;                //���ݣ�ֻ��ĩ�ڵ���Ч��
    QString                 comment;                //ע��
    QString                 UUid;                   //Uid;Ψһ
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
    purpose		:	�ѽṹ��tagTreeAttr�е����ݼ�¼��xml��
                    Ҳ�ܰ�xml�е����ݶ�ȡ����
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
        * @brief    ��¼���е����ݣ��Զ�д����ڵ�
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName���ļ��� filghtAttrs�����ݼ��� rootName�����ڵ�
        * @return	�Ƿ�д��ɹ�
    */
    static bool writeNewXmlConfigFile(QString &fileName,QList<XmlAtrrPtr> filghtAttrs,QString rootName = "xmlConfig");



    /**
        * @fn		writeNewXmlConfigFile(QString &fileName,QList<XmlAtrrPtr> filghtAttrs,QString rootName = "xmlConfig");
        * @brief    ��¼���е�����,�������ڵ�
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName���ļ��� filghtAttrs�����ݼ���
        * @return	�Ƿ�д��ɹ�
    */
    static bool writeXmlConfigFile(QString &fileName,XmlAtrrPtr filghtAttr);

    /**
        * @fn		readNewXmlConfigFile(QString &fileName)const
        * @brief    ��ȡ�������ļ���û�д�����ڵ�
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName:�ļ���
        * @return	���ݼ���
    */
    static QList<XmlAtrrPtr> readNewXmlConfigFile(QString &fileName);

    /**
        * @fn		readNewXmlConfigFile(QString &fileName)const
        * @brief    ��ȡ�������ļ�,֧�ָ��ڵ�
        * @author	zcx
        * @date		2018/6/11
        * @param	fileName:�ļ���
        * @return	���ݼ���
    */
    static XmlAtrrPtr readXmlConfigFile(QString &fileName);

    /**
        * @fn		getAllTagTreeAttr(QList<XmlAtrrPtr> attrs);
        * @brief	ȥ�����ӹ�ϵ
        * @author	zcx
        * @date     2018/10/13
        * @param    attrs:���ݼ���
        * @return   ����
    */
    static QList<XmlAtrrPtr> getAllTagTreeAttr(QList<XmlAtrrPtr> attrs);

    /**
        * @fn		getXmlAttrPtrByUid(QList<XmlAtrrPtr> xmlAtrrs, QString Uid);
        * @brief	ͨ��Uid�õ�XmlAtrrPtr
        * @author	zcx
        * @date		2018/10/13
        * @param	xmlAtrrs�����ݼ��� Uid:Ψһ��ʶ��
        * @return   ����
    */
    static XmlAtrrPtr getXmlAttrPtrByUid(QList<XmlAtrrPtr> xmlAtrrs, QString Uid);

private:
    //���غ�����дһ�����ӽڵ�xml�����ļ�
    static void writeXmlChildConfigFile(XmlAttr *attr, QXmlStreamWriter &xmlStream);

    //��xml�����ļ��ж�һ�����ӽڵ�
    static void readXmlChildConfigFile(QDomElement &parentElement, XmlAttr *parentAttr);

    //��QListת��QString����","�ָ�
    QString QListToQString(QList<QString> attr);

    //��boolת��QString
    QString boolToQString(bool checked);

    //��QStringת��bool
    bool QStringTobool(QString str);

    //������д��xml��
    static void writeData(XmlAttr *attr, QXmlStreamWriter &xmlStream);

    //��xml�е����ݴ���ڽṹ����
    static void readData(QDomElement &element, XmlAttr *attr);


    //������д��xml��
    static void childTagTreeAttr(QList<XmlAtrrPtr> &attrs, XmlAttr *parentAttrs);
};

#endif // CXML_H
