#ifndef HFXML_H
#define HFXML_H
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
            setParentFilgAttr(NULL);
            parent = parentAttr;
            parent->childs.push_back(this);
        }
    }

}XmlAttr,*tXmlAttr;
Q_DECLARE_METATYPE(XmlAttr)
Q_DECLARE_METATYPE(QList<XmlAttr> )

#endif // HFDEFINE_H
