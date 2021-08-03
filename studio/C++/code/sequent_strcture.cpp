#include "sequent_strcture.hpp"
#include "ObjectFactory.h"
#include <iostream>
#include "commondefine.hpp"

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

class SubClass : public Base
{
private:
    /* data */
public:
    using Base::Base;
};


SequentStrctureTest::SequentStrctureTest(/* args */) 
{
    SubClass s(3);
    std::cout << s.value1 << std::endl;
    COUT(s.value2);
}

CUSTOMEGISTER(SequentStrcture,SequentStrctureTest)