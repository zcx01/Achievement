#include "ResponsibilityClient.h"
#include "Responsibility.h"

ResponsibilityClient::ResponsibilityClient()
{
}

ResponsibilityClient::~ResponsibilityClient()
{

}


void ResponsibilityClient::Test()
{
    Handler *h1 = new ConcreteHandler1;
    Handler *h2 = new ConcreteHandler2;
    Handler *h3 = new ConcreteHandler3;
    h1->setSuccessor(h2);
    h2->setSuccessor(h3);

    int requests[] = {2,5,14,22,18,3,27,20};

    for(int i =0; i <8; i++)
    {
        h1->HandlerRequest(requests[i]);
    }

}
MYREGISTER(ResponsibilityClient)
