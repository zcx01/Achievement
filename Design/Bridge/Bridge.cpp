#include "Bridge.h"
#include <QDebug>


void ConcreteImplementA::Operation()
{
    qDebug()<<"具体实现A的方法执行";
}

void ConcreteImplementB::Operation()
{
    qDebug()<<"具体实现B的方法执行";
}

Abstraction::Abstraction()
{
    m_Implement = NULL;
}

void Abstraction::setImplementor(Implement *implement)
{
    m_Implement =implement;
}

void Abstraction::Operation()
{
    if(m_Implement)
        m_Implement->Operation();
}


void RefinedAbstraction::Operation()
{
    if(m_Implement)
        m_Implement->Operation();
}
