#include "Proxy.h"
#include <QDebug>
void RealSubject::Request()
{
    qDebug()<<"真实的请求";
}

Proxy::Proxy()
{
    m_RealSubject = NULL;
}

Proxy::~Proxy()
{

}

void Proxy::Request()
{
    if(m_RealSubject == NULL)
        m_RealSubject = new  RealSubject;
    m_RealSubject->Request();
}
