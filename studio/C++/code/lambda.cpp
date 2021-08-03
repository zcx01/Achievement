#include "lambda.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <utility>
#include <memory>

template <typename T>
void CallCout(T fun)
{
    COUT(fun());
}

//值捕获
void lambda_value_capture()
{
    int value = 1;
    auto copy_value = [value]{
        return value;
    };
    value = 100;
    auto stroed_value = copy_value();
    COUT(stroed_value)
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

//引用捕获
void lambda_reference_capture()
{
    int value = 1;
    auto copy_value = [&value](){
        return value;
    };
    value = 200;
    auto stroed_value = copy_value();
    COUT(stroed_value)
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用

    COUT(typeid(copy_value).name())
    CallCout([&value](){
        return value;
    });
    CallCout(copy_value);// 传递闭包对象，隐式转换为 T* 类型的函数指针值

}

//隐式捕获
void lambda_implicit_capture()
{
    COUT("-----------------隐式捕获")
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    auto empty =[](){
        COUT("空值捕获")
    };
    auto t_value=[value1,value2](){
        COUT("捕获一系列变量")
        COUT(value1)
        COUT(value2)
    };
    auto reference = [&]()
    {
        COUT("引用捕获")
        COUT(value1)
        COUT(value2)
        COUT(value3)
    }; 
    auto value = [=]()
    {
        COUT("值捕获")
        COUT(value1)
        COUT(value2)
        COUT(value3)
    };
    empty();
    t_value();
    value1=4;
    value2=5;
    value3=6;
    value();
    reference();
}

void lambda_expression_capture()
{
    auto important =std::make_unique<int>(1);
    //important 是一个独占指针，是不能够被 "=" 值捕获到，这时候我们可以将其转移为右值，在表达式中初始化
    auto add = [v1 = 1, v2= std::move(important)](int x,int y)->int
    {
        return x+y+v1+(*v2);
    };
    COUT("表达式捕获")
    COUT(add(3,4))
}

void lambda_auto()
{
    COUT("泛型 Lambda")
    auto add=[](auto x, auto y){
        return x+y;
    };
    COUT(add(1,2))
    COUT(add(1.1,2.2))
    COUT(add(1.1, 2))
}
LambdaTest::LambdaTest(/* args */) 
{
    lambda_value_capture();
    lambda_reference_capture();
    lambda_implicit_capture();
    lambda_expression_capture();
    lambda_auto();
}

CUSTOMEGISTER(Lambda,LambdaTest)