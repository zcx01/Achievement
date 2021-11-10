#include "test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

TestTest::TestTest(/* args */) 
{
    std::map<std::string,std::string> data;
    if (data["dsss"] != "dssssfd")
    {
         COUT(data["dsss"]<<" "<<"dssssfd")
    }
    
   
}

CUSTOMEGISTER(Test,TestTest)