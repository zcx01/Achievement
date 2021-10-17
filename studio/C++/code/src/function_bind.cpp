#include "function_bind.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <algorithm>

int foo(int a,int b,int c)
{
    return b;
}

template<typename T>
void call(T f)
{
    f(9);
}

void FunctionBind::dealData() 
{
    int result = 20;
    callFun(result);
}

void FunctionBind::registerFun(CustiomFum f) 
{
    callFun = f;    
}

FunctionBindTest::FunctionBindTest(/* args */) 
{
    auto bindFoo = std::bind(foo,1,std::placeholders::_1,1);
    COUT(bindFoo(2));

    std::function<int(int)> func = std::bind(foo,1,std::placeholders::_1,1);
    COUT(func(3));

    std::function<void(int)> func1= std::bind(&FunctionBindTest::printValue,this,std::placeholders::_1);
    func1(12);
    call(func1);

    // std::function<bool(int,int)> func2 = std::bind(&FunctionBindTest::Comp,this,std::placeholders::_1,std::placeholders::_2);
    auto func2 = std::bind(&FunctionBindTest::Comp,this,std::placeholders::_1,std::placeholders::_2);
    
    std::vector<int> ivs;
    ivs.push_back(1);
    ivs.push_back(3);
    ivs.push_back(21);

    std::sort(ivs.begin(),ivs.end(),func2);
    COUTI(ivs);

    FunctionBind fb;
    fb.registerFun(std::bind(&FunctionBindTest::printValue,this,std::placeholders::_1));
    fb.dealData();
    
}

CUSTOMEGISTER(FunctionBind,FunctionBindTest)
void FunctionBindTest::printValue(int v) 
{
    COUT(v);
}

bool FunctionBindTest::Comp(int f, int t) 
{
    if( f > commad)
        return true;
    else 
        return f < t;
}


