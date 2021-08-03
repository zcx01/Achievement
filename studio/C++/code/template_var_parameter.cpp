#include "template_var_parameter.hpp"
#include "ObjectFactory.h"
#include <iostream>
#include <initializer_list>

template<typename ... Ts>
void magic(Ts ... args){
    std::cout << sizeof ...(args) << std::endl;//获取参数的个数
}

//初始化列表展开，解参数包
/**
 * 通过初始化列表，(lambda 表达式, value)... 将会被展开。
 * 由于逗号表达式的出现，首先会执行前面的 lambda 表达式，完成参数的输出。
 *  为了避免编译器警告，我们可以将 std::initializer_list 显式的转为 void。
*/
template<typename T,typename ... Ts>
auto printf3(T value,Ts ... args){
    std::cout<< value << std::endl;
    (void)std::initializer_list<T>{
        (
            [&args]{
                std::cout << args << std::endl;
            }(),
        value)...
    };
}

//折叠表达式
template<typename ... Ts>
auto sum(Ts ... args){
    return (args + ...);
}

//非类型模板参数推导
template <auto value> void foo()
{
    std::cout <<value << std::endl;
}

TemplateVarParameterTest::TemplateVarParameterTest(/* args */) 
{
    magic("s",1,2,"s");
    printf3("sdddd",1,2,"seeee");
    std::cout<<sum(12,14,25,35,14,25,356,1)<<std::endl;
    foo<10>();
}

CUSTOMEGISTER(TemplateVarParameter,TemplateVarParameterTest)