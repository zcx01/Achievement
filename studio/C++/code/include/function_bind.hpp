#pragma once
#include <string>
#include <functional>

using  CustiomFum = std::function<void(int)>;
class FunctionBind
{
public:

    void dealData();

    void registerFun(CustiomFum f);

    CustiomFum callFun;
};


class FunctionBindTest
{
private:
    /* data */
public:
    FunctionBindTest(/* args */);

    void printValue(int v);

    bool Comp(int f,int t);
private:
    std::string value = "FunctionBind";

    int commad=10;
};

