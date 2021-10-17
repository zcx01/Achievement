#include "enum_class.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

enum class new_class : unsigned int
{
    value1,
    value2,
    value3=100,
    value4=100
};
enum class new_class1 : unsigned int
{
    value1,
    value2,
    value3=100,
    value4=100
};

//枚举值可以输出
template<typename T>
std::ostream & operator <<(typename std::enable_if<std::is_enum<T>::value,std::ostream>::type &stream,const T &e)
{
    return stream <<static_cast<typename std::underlying_type<T>::type>(e);
};

EnumClassTest::EnumClassTest(/* args */) 
{
    // int v = new_class::value1;//非法
    int v =(int)new_class::value1;//合法
    COUT(v)
    // if(new_class::value1 == 0){} //非法
    // if(new_class::value1 == new_class1::value1)//非法
    if(new_class1::value3 == new_class1::value4)//合法
    {
        COUT("value3==value4")
    }
    COUT(new_class::value2)
}

CUSTOMEGISTER(EnumClass,EnumClassTest)