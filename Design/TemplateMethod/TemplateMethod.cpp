#include "TemplateMethod.h"
#include <QDebug>

void AbstractClass::TemplateMethod()
{
    PrimitiveOperation1();
    PrimitiveOperation2();
    qDebug()<<"";
}


void ConcreteClassA::PrimitiveOperation1()
{
    qDebug()<<"具体类A方法1的实现";
}

void ConcreteClassA::PrimitiveOperation2()
{
    qDebug()<<"具体类A方法2的实现";
}

void ConcreteClassB::PrimitiveOperation1()
{
    qDebug()<<"具体类B方法1的实现";
}

void ConcreteClassB::PrimitiveOperation2()
{
    qDebug()<<"具体类B方法2的实现";
}
