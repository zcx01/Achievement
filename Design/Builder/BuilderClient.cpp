#include "BuilderClient.h"
#include "Builder.h"

BuilderClient::BuilderClient()
{
}

BuilderClient::~BuilderClient()
{

}

void BuilderClient::Test()
{
    Director d;
    Builder *b1 = new ConcreteBuilder1;
    Builder *b2 = new ConcreteBuilder2;

    d.Construct(b1);//指挥者用ConcreteBuilder1的方法来创建产品
    Product *p1 = b1->GetResult();
    p1->Show();

    d.Construct(b2);//指挥者用ConcreteBuilder2的方法来创建产品
    Product *p2 = b2->GetResult();
    p2->Show();
}

MYREGISTER(BuilderClient)
