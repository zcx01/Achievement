#include "Responsibility.h"
#include <QDebug>

Handler::Handler()
{
    m_Successor = NULL;
}

void Handler::setSuccessor(Handler *successor)
{
    m_Successor =successor;
}


void ConcreteHandler1::HandlerRequest(int request)
{
    if(request >=0 && request <10)
    {
        qDebug()<<QString("%1 处理请求 %2").arg("ConcreteHandler1").arg(request);
    }
    else if(m_Successor != NULL)
    {
        m_Successor->HandlerRequest(request);
    }
}
void ConcreteHandler2::HandlerRequest(int request)
{
    if(request >=10 && request <20)
    {
        qDebug()<<QString("%1 处理请求 %2").arg("ConcreteHandler2").arg(request);
    }
    else if(m_Successor != NULL)
    {
        m_Successor->HandlerRequest(request);
    }
}

void ConcreteHandler3::HandlerRequest(int request)
{
    if(request >=20 && request <30)
    {
        qDebug()<<QString("%1 处理请求 %2").arg("ConcreteHandler2").arg(request);
    }
    else if(m_Successor != NULL)
    {
        m_Successor->HandlerRequest(request);
    }
}
