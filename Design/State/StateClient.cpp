#include "StateClient.h"
#include "State.h"

StateClient::StateClient()
{
}

StateClient::~StateClient()
{

}

void StateClient::Test()
{
    Context s(new ConcreteStateA);//初始化状态为ConcreteStateA

    //不断的改变请求，同时改变状态
    s.Request();
    s.Request();
    s.Request();
    s.Request();
}
MYREGISTER(StateClient)
