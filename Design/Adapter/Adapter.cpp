#include "Adapter.h"
#include <QDebug>

void Target::Request()
{
    qDebug()<<"普通请求!";
}

void Adaptee::SpecificRequest()
{
    qDebug()<<"特殊请求!";
}

Adapter::Adapter()
{
    m_Adaptee = new Adaptee();
}

Adapter::~Adapter()
{
    delete m_Adaptee;
}

void Adapter::Request()
{
    m_Adaptee->SpecificRequest();
}
