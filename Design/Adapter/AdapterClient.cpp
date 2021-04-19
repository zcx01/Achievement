#include "AdapterClient.h"
#include "Adapter.h"

AdapterClient::AdapterClient()
{
}

AdapterClient::~AdapterClient()
{

}

void AdapterClient::Test()
{
    Target *t = new Adapter;
    t->Request();
}
MYREGISTER(AdapterClient)
