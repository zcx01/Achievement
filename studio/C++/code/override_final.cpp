#include "override_final.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

class Base{
public:
    virtual void foo(int);
    virtual void foo1(int) final;
};

class SubClass : public Base
{
public:
    virtual void foo(int) override;
    // virtual void foo(float) override;   //非法，父类中没有此虚函数
};

class SubClass1 final : Base
{
    //合法
};

// class SubClass2 : SubClass1{}; //非法
class SubClass3 : Base
{
    // virtual void foo1(int);//非法 ，foo1 已经final
};


OverrideFinalTest::OverrideFinalTest(/* args */) 
{

}

CUSTOMEGISTER(OverrideFinal,OverrideFinalTest)