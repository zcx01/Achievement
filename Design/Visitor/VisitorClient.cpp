#include "VisitorClient.h"
#include "Visitor.h"

VisitorClient::VisitorClient()
{
}

VisitorClient::~VisitorClient()
{

}

void VisitorClient::Test()
{
    ObjectStruct o;
    o.Attch(new ConcreteElementA);
    o.Attch(new ConcreteElementB);

    Visitor *v1 = new ConcreteVisitor1;
    Visitor *v2 = new ConcreteVisitor2;
    o.Accept(v1);
    o.Accept(v2);

}
MYREGISTER(VisitorClient)
