#include "BridgeClient.h"
#include "Bridge.h"

BridgeClient::BridgeClient()
{
}

BridgeClient::~BridgeClient()
{

}

void BridgeClient::Test()
{
    Abstraction *ab = new RefinedAbstraction;

    ab->setImplementor(new ConcreteImplementA);
    ab->Operation();

    ab->setImplementor(new ConcreteImplementB);
    ab->Operation();
}
MYREGISTER(BridgeClient)
