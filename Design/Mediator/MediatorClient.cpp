#include "MediatorClient.h"
#include "Mediator.h"

MediatorClient::MediatorClient()
{
}

MediatorClient::~MediatorClient()
{

}

void MediatorClient::Test()
{
    ConcreteMediator *m = new ConcreteMediator();

    Colleague *c1 = new ConcreteColleague1(m);
    Colleague *c2 = new ConcreteColleague2(m);

    m->addColleague(c1);
    m->addColleague(c2);

    c1->send("吃过饭了吗？");
    c2->send("没有呢，你打算请客吗？");
}
MYREGISTER(MediatorClient)
