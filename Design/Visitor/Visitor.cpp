#include "Visitor.h"
#include <QDebug>

void ConcreteVisitor1::VisitorConcreteElementA(ConcreteElementA *concreteElementA)
{
    qDebug()<<QString("%1被%2访问").arg(concreteElementA->getName()).arg("ConcreteVisitor1");
}

void ConcreteVisitor1::VisitorConcreteElementB(ConcreteElementB *concreteElementB)
{
    qDebug()<<QString("%1被%2访问").arg(concreteElementB->getName()).arg("ConcreteVisitor1");
}

void ConcreteVisitor2::VisitorConcreteElementA(ConcreteElementA *concreteElementA)
{
    qDebug()<<QString("%1被%2访问").arg(concreteElementA->getName()).arg("ConcreteVisitor2");
}

void ConcreteVisitor2::VisitorConcreteElementB(ConcreteElementB *concreteElementB)
{
    qDebug()<<QString("%1被%2访问").arg(concreteElementB->getName()).arg("ConcreteVisitor2");
}


void ConcreteElementA::Accpet(Visitor *visitor)
{
    visitor->VisitorConcreteElementA(this);
}

QString ConcreteElementA::getName()
{
    return "ConcreteElementA";
}

void ConcreteElementA::OprationA()
{

}
void ConcreteElementB::Accpet(Visitor *visitor)
{
    visitor->VisitorConcreteElementB(this);
}

QString ConcreteElementB::getName()
{
    return "ConcreteElementB";
}

void ConcreteElementB::OprationB()
{

}

void ObjectStruct::Attch(Element *element)
{
    m_Elements.push_back(element);
}

void ObjectStruct::Detach(Element *element)
{
    m_Elements.removeOne(element);
}

void ObjectStruct::Accept(Visitor *visitor)
{
    for(int i =0; i <m_Elements.size(); i++)
    {
        m_Elements.at(i)->Accpet(visitor);
    }
}
