#include "ProxyClient.h"
#include "Proxy.h"

ProxyClient::ProxyClient()
{

}

void ProxyClient::Test()
{
    Proxy *p = new Proxy;
    p->Request();
}

MYREGISTER(ProxyClient)
