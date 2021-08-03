#include "delegation_structure.hpp"
#include "ObjectFactory.h"
#include <iostream>
class Base
{
private:
    /* data */
public:
    int value1;
    int value2;
    Base(/* args */)
    {
        value1 = 1;
    }
    Base(int value): Base(){
        value2 = value;
    }
};



DelegationStructureTest::DelegationStructureTest(/* args */) 
{
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;
}

CUSTOMEGISTER(DelegationStructure,DelegationStructureTest)