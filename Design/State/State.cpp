#include "State.h"
#include <QDebug>

Context::Context(State *state)
{
    setState(state);
}

void Context::setState(State *state)
{
    m_State = state;
    if(m_State)
        qDebug()<<QString("当前状态：%1").arg(m_State->getName());
}

State *Context::getState()
{
    return m_State;
}

void Context::Request()
{
    if(m_State)
        m_State->Handle(this);
}

void ConcreteStateA::Handle(Context *context)
{
    context->setState(new ConcreteStateB);
}

QString ConcreteStateA::getName()
{
    return "ConcreteStateA";
}
void ConcreteStateB::Handle(Context *context)
{
    context->setState(new ConcreteStateA);
}

QString ConcreteStateB::getName()
{
    return "ConcreteStateB";
}
