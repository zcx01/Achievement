#include "Composite.h"
#include <QDebug>

Component::Component(QString name)
{
    this->m_Name =name;
}

void Component::Display(int depth)
{
    QString content;
    for(int i=0; i <depth; i++)
        content +="*";
    content += m_Name;
    qDebug()<<content;
}

void Leaf::add(Component *c)
{
    qDebug()<<"Cannot add to a leaf";
}

void Leaf::remove(Component *c)
{
    qDebug()<<"Cannot remove to a leaf";
}

void Composite::add(Component *c)
{
    m_Children.push_back(c);
}

void Composite::remove(Component *c)
{
    m_Children.removeAll(c);
}

void Composite::Display(int depth)
{
    Component::Display(depth);

    foreach (Component *c, m_Children)
    {
        c->Display(depth+1);
    }
}
