#include "decltype_auto.hpp"
#include "ObjectFactory.h"
#include <iostream>

decltype(auto) look_up_a_string_1() 
{
    decltype_auto t;
    return t.lookup1();    
}

DecltypeAutoTest::DecltypeAutoTest(/* args */) 
{
    decltype_auto t;
    // auto s=look_up_a_string_1();
    std::cout<<look_up_a_string_1()<<std::endl;
}

CUSTOMEGISTER(DecltypeAuto,DecltypeAutoTest)

decltype_auto::decltype_auto(/* args */) 
{
    str="abcdefg";
}

std::string decltype_auto::lookup1() 
{
    return str;
}

std::string& decltype_auto::lookup2() 
{
    return str;
}




decltype(auto) look_up_a_string_2() 
{
    // return lookup2();    
}

