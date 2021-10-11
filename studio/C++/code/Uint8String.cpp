#include "Uint8String.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

Uint8StringTest::Uint8StringTest(/* args */) 
{
    std::string test = "dadasdsdsad";
    std::vector<uint8_t> uint8S(test.begin(),test.end());
    COUTI(uint8S);

    std::string test2(uint8S.begin(),uint8S.end());
    COUT(test2)
}

CUSTOMEGISTER(Uint8String,Uint8StringTest)