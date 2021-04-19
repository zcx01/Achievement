#include "TemplateMethodClient.h"
#include "TemplateMethod.h"
TemplateMethodClient::TemplateMethodClient()
{
}

TemplateMethodClient::~TemplateMethodClient()
{

}

void TemplateMethodClient::Test()
{
    AbstractClass *c;
    c = new ConcreteClassA;
    c->TemplateMethod();

    c = new ConcreteClassB();
    c->TemplateMethod();
}

MYREGISTER(TemplateMethodClient)
