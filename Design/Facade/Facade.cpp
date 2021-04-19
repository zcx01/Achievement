#include "Facade.h"
#include <QDebug>

void SubSystemOne::MethodOne()
{
    qDebug()<<"子系统方法一";
}

void SubSystemTwo::MethodTwo()
{
    qDebug()<<"子系统方法二";
}

void SubSystemThree::MethodThree()
{
    qDebug()<<"子系统方法三";
}

void SubSystemFour::MethodFour()
{
    qDebug()<<"子系统方法四";
}

Facade::Facade()
{
    m_SubSystemOne = new SubSystemOne();
    m_SubSystemTwo = new SubSystemTwo();
    m_SubSystemThree = new SubSystemThree();
    m_SubSystemFour= new SubSystemFour();
}

Facade::~Facade()
{
    delete m_SubSystemOne;
    delete m_SubSystemTwo;
    delete m_SubSystemThree;
    delete m_SubSystemFour;
}

void Facade::MethodA()
{
    qDebug()<<"方法组A()";
    m_SubSystemOne->MethodOne();
    m_SubSystemTwo->MethodTwo();
    m_SubSystemThree->MethodThree();
    m_SubSystemFour->MethodFour();
}

void Facade::MethodB()
{
    qDebug()<<"方法组B()";
    m_SubSystemTwo->MethodTwo();
    m_SubSystemThree->MethodThree();
}
