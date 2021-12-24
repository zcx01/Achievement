#include "sendmulti_type_can_value.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

SendmultiTypeCanValueTest::SendmultiTypeCanValueTest(/* args */) 
{
    SendmultiTypeCanValue().SendCanValue(std::make_tuple("ddd",12));
}

CUSTOMEGISTER(SendmultiTypeCanValue,SendmultiTypeCanValueTest)