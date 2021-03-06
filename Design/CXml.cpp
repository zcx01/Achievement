#include "CXml.h"
#include <QtXml/QDomComment>
#include <QCheckBox>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>

CXml::CXml()
{

}

CXml::~CXml()
{

}

bool CXml::writeNewXmlConfigFile(QString &fileName,QList<XmlAtrrPtr> filghtAttrs,QString rootName)
{
    QList<XmlAtrrPtr> m_FightAttrs = filghtAttrs;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QXmlStreamWriter xmlStream(&file);
        xmlStream.setAutoFormatting(true);
        xmlStream.writeStartDocument();
        xmlStream.writeStartElement(rootName);
        QList<XmlAttr *> rootFightAttrs;
        for(int i = 0 ;i <m_FightAttrs.size() ;i++)
        {
            XmlAttr * attr = m_FightAttrs.at(i).data();
            while(attr->parent != NULL)
                attr = attr->parent;
            if(!rootFightAttrs.contains(attr))
                rootFightAttrs.append(attr);
        }
        for(int i = 0 ;i <rootFightAttrs.size() ;i++)
        {
            XmlAttr *rooAttr = rootFightAttrs.at(i);
            if(rooAttr == NULL) continue;
            writeData(rooAttr,xmlStream);
            writeXmlChildConfigFile(rooAttr,xmlStream);
            xmlStream.writeEndElement();
        }
        xmlStream.writeEndElement();
        xmlStream.writeEndDocument();
        file.close();
    }
    else
        return false;
    return true;
}

bool CXml::writeXmlConfigFile(QString &fileName, XmlAtrrPtr filghtAttr)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        XmlAttr * rootFightAttrs =filghtAttr.data();
        if(rootFightAttrs == NULL) return false;
        while(rootFightAttrs->parent != NULL)
            rootFightAttrs = rootFightAttrs->parent;

        QXmlStreamWriter xmlStream(&file);
        xmlStream.setAutoFormatting(true);
        xmlStream.writeStartDocument();
        writeData(rootFightAttrs,xmlStream);
        writeXmlChildConfigFile(rootFightAttrs,xmlStream);
        xmlStream.writeEndDocument();
        file.close();
    }
    else
        return false;
    return true;
}

QList<XmlAtrrPtr>  CXml::readNewXmlConfigFile(QString &fileName)
{
    QList<XmlAtrrPtr> XmlAtrrPtrs;
    QDomDocument dom;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite))
    {
        return XmlAtrrPtrs;
    }
    //??????????????????xml????????????
    if (!dom.setContent(&file))
    {
        file.close();
        return XmlAtrrPtrs;
    }
    QDomElement root = dom.documentElement();
    if(root.hasChildNodes())
    {
        QDomNodeList node_list = root.childNodes();
        for(int i = 0 ; i <node_list.size(); i++)
        {
            QDomElement domElement = node_list.at(i).toElement();
            if(domElement.nodeType() != QDomElement::ElementNode || domElement.toElement().tagName().isEmpty() )
                continue;
            XmlAttr *firstAttr = new XmlAttr;
            readData(domElement,firstAttr);
            firstAttr->parent = NULL;
            readXmlChildConfigFile(domElement,firstAttr);
            XmlAtrrPtrs.push_back(XmlAtrrPtr(firstAttr));
        }
    }
    file.close();
    return XmlAtrrPtrs;
}

XmlAtrrPtr CXml::readXmlConfigFile(QString &fileName)
{
    XmlAtrrPtr atrrPtr(new XmlAttr);
    QDomDocument dom;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite))
    {
        return atrrPtr;
    }
    //??????????????????xml????????????
    if (!dom.setContent(&file))
    {
        file.close();
        return atrrPtr;
    }
    QDomElement root = dom.documentElement();

    readData(root,atrrPtr.data());

    if(root.hasChildNodes())
    {
        QDomNodeList node_list = root.childNodes();
        for(int i = 0 ; i <node_list.size(); i++)
        {
            QDomElement domElement = node_list.at(i).toElement();
            if(domElement.nodeType() != QDomElement::ElementNode || domElement.toElement().tagName().isEmpty() )
                continue;
            XmlAttr *firstAttr = new XmlAttr;
            readData(domElement,firstAttr);
            firstAttr->parent = NULL;
            readXmlChildConfigFile(domElement,firstAttr);
            atrrPtr.data()->childs.push_back(firstAttr);
        }
    }
    file.close();
    return atrrPtr;
}

QList<XmlAtrrPtr> CXml::getAllTagTreeAttr(QList<XmlAtrrPtr> attrs)
{
    QList<XmlAtrrPtr> tagTreeAttrs;
    QList<XmlAttr *> rootFightAttrs;
    for(int i = 0 ;i <attrs.size() ;i++)
    {
        XmlAttr * attr = attrs.at(i).data();
        while(attr->parent != NULL)
            attr = attr->parent;
        if(!rootFightAttrs.contains(attr))
            rootFightAttrs.append(attr);
    }
    for(int i = 0 ;i <rootFightAttrs.size() ;i++)
    {
        XmlAttr *attr = rootFightAttrs.at(i);
        if(attr == NULL) continue;
        tagTreeAttrs.push_back(XmlAtrrPtr(attr));
        childTagTreeAttr(tagTreeAttrs,attr);
    }
    return tagTreeAttrs;
}

XmlAtrrPtr CXml::getXmlAttrPtrByUid(QList<XmlAtrrPtr> xmlAtrrs, QString Uid)
{
    QList<XmlAtrrPtr> attrs = getAllTagTreeAttr(xmlAtrrs);
    foreach (XmlAtrrPtr attr, attrs)
    {
        if(attr->UUid == Uid)
            return attr;
    }
    return XmlAtrrPtr();
}

void CXml::writeXmlChildConfigFile(XmlAttr *attr, QXmlStreamWriter &xmlStream)
{
    foreach(XmlAttr *childAttr, attr->childs)
    {
        if(childAttr == NULL) continue;
        writeData(childAttr,xmlStream);
        writeXmlChildConfigFile(childAttr,xmlStream);
        xmlStream.writeEndElement();
    }
}

void CXml::readXmlChildConfigFile(QDomElement &parentElement, XmlAttr *parentAttr)
{
    QDomNodeList node_list = parentElement.childNodes();
    for(int i = 0 ; i <node_list.size(); i++)
    {
        QDomElement domElement = node_list.at(i).toElement();
        if(domElement.nodeType() != QDomElement::ElementNode || domElement.toElement().tagName().isEmpty() ) continue;
        XmlAttr *attr = new XmlAttr;
        readData(domElement,attr);
        attr->setParentFilgAttr(parentAttr);
        readXmlChildConfigFile(domElement,attr);
    }
}

QString CXml::QListToQString(QList<QString> attr)
{
    QString remarks;
    for(int i= 0; i<attr.size();i++)
    {
        if(i == attr.size()-1)
            remarks+= attr.at(i);
        else
            remarks+=attr.at(i)+",";
    }
    return remarks;
}

QString CXml::boolToQString(bool checked)
{
    if(checked)
        return "true";
    else
        return "false";
}

bool CXml::QStringTobool(QString str)
{
    if(str == "true")
        return true;
    else
        return false;
}

void CXml::writeData(XmlAttr *attr, QXmlStreamWriter &xmlStream)
{
    if(!attr->comment.isEmpty()) xmlStream.writeComment(attr->comment);
    if(!attr->tagName.isEmpty())
        xmlStream.writeStartElement(attr->tagName);
    else
        xmlStream.writeStartElement("node");
    for(int i =0; i < attr->attrs.size(); i++)
        xmlStream.writeAttribute(attr->attrs.keys().at(i),attr->attrs.values().at(i).toString());
    if(attr->childs.isEmpty()) xmlStream.writeCharacters(attr->content);
}

void CXml::readData(QDomElement &element, XmlAttr *attr)
{
    attr->tagName = element.tagName();
    for(int i=0; i < element.attributes().size(); i++)
    {
        QDomAttr domAttr = element.attributes().item(i).toAttr();
        attr->attrs.insert(domAttr.name(),domAttr.value());
    }
    if(!element.childNodes().isEmpty())
    {
        if(element.childNodes().at(0).nodeType() != QDomElement::ElementNode)
            attr->content = element.childNodes().at(0).toText().data();
    }
    if(element.previousSibling().nodeType() == QDomElement::CommentNode)
        attr->comment = element.previousSibling().toComment().data();
}

void CXml::childTagTreeAttr(QList<XmlAtrrPtr> &attrs, XmlAttr *parentAttrs)
{
    foreach(XmlAttr *childAttr, parentAttrs->childs)
    {
        if(childAttr == NULL) continue;
        attrs.push_back(XmlAtrrPtr(childAttr));
        childTagTreeAttr(attrs,childAttr);
    }

}
