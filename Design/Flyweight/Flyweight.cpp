#include "Flyweight.h"
#include <QDebug>

Flyweight::Flyweight()
{

}


void ConcreteFlyweight::Operation(int extrinsicstate)
{
    qDebug()<<QString("具体Flyweight:%1").arg(QString::number(extrinsicstate));
}


void UnSharedConcreteFlyweight::Operation(int extrinsicstate)
{
    qDebug()<<QString("不共享的具体Flyweight:%1").arg(QString::number(extrinsicstate));
}
FlyweightFactory::FlyweightFactory()
{
    m_Flyweights.insert("X",new ConcreteFlyweight);
    m_Flyweights.insert("Y",new ConcreteFlyweight);
    m_Flyweights.insert("Z",new ConcreteFlyweight);
}

Flyweight *FlyweightFactory::getFlyweight(QString key)
{
    return m_Flyweights.value(key);
}
