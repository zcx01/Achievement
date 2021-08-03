#include "right_value.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

std::vector<int> foo()
{
    std::vector<int> temp ={1,2,3,4};
    return temp;//temp 是一个将亡值
}


void reference(std::string & str)
{
    COUT("左值")
}

void reference(std::string && str)
{
    COUT("右值")
}

RightValueTest::RightValueTest(/* args */) 
{
    std::string lv1 = "string"; //lv1是一个左值
    // std::string && r1 = lv1; //非法，右值引用不能引用左值
    std::string && rv1 = std::move(lv1); //合法，std::move可以将左值移为右值
    COUT(rv1)
    rv1="str";
    COUT(rv1<<" "<<lv1)//输出 str str

    const std::string & lv2 = lv1 + lv1;// 合法, 常量左值引用能够延长临时变量的生命周期， lv1 + lv1不会产生临时变量 lv2 不能修改
    COUT(lv2)

    std::string&& rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
    rv2+="test";
    COUT(rv2)

    reference(rv2);//虽然引用了一个右值，但由于它是一个引用，所以 rv2 依然是一个左值
}

CUSTOMEGISTER(RightValue,RightValueTest)