#include "FacadeClient.h"
#include "Facade.h"

FacadeClient::FacadeClient()
{

}

FacadeClient::~FacadeClient()
{

}


void FacadeClient::Test()
{
    Facade f;
    f.MethodA();
    f.MethodB();
}
MYREGISTER(FacadeClient)
