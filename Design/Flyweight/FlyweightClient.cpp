#include "FlyweightClient.h"
#include "Flyweight.h"

FlyweightClient::FlyweightClient()
{
}

FlyweightClient::~FlyweightClient()
{

}


void FlyweightClient::Test()
{
    int extrinsicstate = 22;

    FlyweightFactory f;

    Flyweight *fx =f.getFlyweight("X");
    fx->Operation(--extrinsicstate);

    Flyweight *fy =f.getFlyweight("Y");
    fy->Operation(--extrinsicstate);

    Flyweight *fz =f.getFlyweight("Z");
    fz->Operation(--extrinsicstate);

    Flyweight *uf = new  UnSharedConcreteFlyweight;
    uf->Operation(--extrinsicstate);
}

MYREGISTER(FlyweightClient)
