#include "initializer_list.hpp"
#include "ObjectFactory.h"
#include <iostream>

InitializerListTest::InitializerListTest(/* args */)
{
    MyInitializer_list list = {1, 2, 3, 4, 5, 6};
    list.foo({7,8,9});
    MyInitializer_list list2{11, 12, 13, 14, 15, 16};
    MyCustionClass myClass{17,18};
}

CUSTOMEGISTER(InitializerList, InitializerListTest)

MyInitializer_list::MyInitializer_list(std::initializer_list<int> list)
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        std::cout << *iter << std::endl;
    }
}

void MyInitializer_list::foo(std::initializer_list<int> list)
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        std::cout << *iter << std::endl;
    }
}

MyCustionClass::MyCustionClass(int t1, int t2) 
{
    std::cout<<t1<<t2<<std::endl;    
}
