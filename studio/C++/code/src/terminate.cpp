#include "terminate.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <exception>

using namespace std;

void customTerminate()
{
    COUT("error");
    exit(0);
}

void (*old_terminate)() = set_terminate(customTerminate);

terminateTest::terminateTest(/* args */) 
{
    throw 'c';
}

CUSTOMEGISTER(terminate,terminateTest)