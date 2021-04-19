#include "Strategy.h"
#include <QDebug>
#include "../ObjectFactory/ObjectFactory.h"
Strategy::Strategy()
{
}

Strategy::~Strategy()
{

}

void ConcreteStrategyA::AlgorithmInterface()
{
    qDebug()<<"算法A实现";
}
MYREGISTER(ConcreteStrategyA)
void ConcreteStrategyB::AlgorithmInterface()
{
    qDebug()<<"算法B实现";
}
MYREGISTER(ConcreteStrategyB)
void ConcreteStrategyC::AlgorithmInterface()
{
     qDebug()<<"算法C实现";
}
MYREGISTER(ConcreteStrategyC)

Context::Context(Strategy *strategy)
{
    m_Strategy = strategy;
}

Context::~Context()
{
    if(m_Strategy)
        delete m_Strategy;
}

void Context::ContextInterface()
{
    m_Strategy->AlgorithmInterface();
}

Context *StrategyObject::creatorObject(QByteArray className)
{
    return new Context(static_cast<Strategy *>(ObjectFactory::createObject(className)));
}

