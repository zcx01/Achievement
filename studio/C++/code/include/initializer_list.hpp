#pragma once
#include <initializer_list>
class InitializerListTest
{
private:
    /* data */
public:
    InitializerListTest();
};

class MyInitializer_list
{
private:
    /* data */
public:
    MyInitializer_list(std::initializer_list<int> list);
    void foo(std::initializer_list<int> list);
};

class MyCustionClass
{
public:
    MyCustionClass(int t1,int t2);
};

