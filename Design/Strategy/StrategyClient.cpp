#include "StrategyClient.h"
#include "Strategy.h"
#include "../ObjectFactory/ObjectFactory.h"

StrategyClient::StrategyClient()
{

}

StrategyClient::~StrategyClient()
{

}

void StrategyClient::Test()
{
//普通的方法
    Context *context;
    context = new Context(new ConcreteStrategyA);
    context->ContextInterface();

    context = new Context(new ConcreteStrategyB);
    context->ContextInterface();

    context = new Context(new ConcreteStrategyC);
    context->ContextInterface();
//+简单工厂+反射
    context =StrategyObject::creatorObject("ConcreteStrategyA");
    context->ContextInterface();
    context =StrategyObject::creatorObject("ConcreteStrategyB");
    context->ContextInterface();
    context =StrategyObject::creatorObject("ConcreteStrategyC");
    context->ContextInterface();
}
MYREGISTER(StrategyClient)
