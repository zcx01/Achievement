#include "PrototypeClient.h"
#include "Prototype.h"

PrototypeClient::PrototypeClient()
{
}

PrototypeClient::~PrototypeClient()
{

}


void PrototypeClient::Test()
{
    Prototype *p1 = new ConcretePrototype1("测试");
    Prototype *p2 = p1->clone();
//    p2->setStr("1111111");
    qDebug()<<p2->getStr()<<p1->getStr();
}
MYREGISTER(PrototypeClient)
