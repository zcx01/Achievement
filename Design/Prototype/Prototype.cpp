#include "Prototype.h"

Prototype::Prototype(QString str)
{
    setStr(str);
}

QString Prototype::getStr()
{
    return m_Str;
}

void Prototype::setStr(QString str)
{
    m_Str = str;
}


ConcretePrototype1::ConcretePrototype1(QString id) : Prototype(id)
{

}

Prototype *ConcretePrototype1::clone()
{
    return (new ConcretePrototype1(getStr()));
}
