
#include "tuple.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

auto get_student(int id)
{
    if(id == 0)
        return std::make_tuple(3.8,'A',"张三");
    if(id == 1)
        return std::make_tuple(2.9,'C',"李四");
    if(id == 2)
        return std::make_tuple(1.7,'D',"王五");

    return std::make_tuple(0.0,'D',"null");
}

TupleTest::TupleTest(/* args */) 
{
    auto student = get_student(0);
    COUT("ID:0"
         << " "
         << "GPA:" << std::get<0>(student) << ","
         << "成绩:" << std::get<1>(student) << ","
         << "姓名:" << std::get<2>(student));
    // COUT(std::get<3>(student)) 非法编译错误

    double gpa;
    char grade;
    std::string name;

    std::tie(gpa,grade,name) = get_student(1);
    COUT("ID:0"
         << " "
         << "GPA:" << gpa << ","
         << "成绩:" << grade << ","
         << "姓名:" << name);

    auto [gpa_,grade_,name_] = get_student(2);//C++ 17
    COUT("ID:0"
         << " "
         << "GPA:" << gpa_ << ","
         << "成绩:" << grade_ << ","
         << "姓名:" << name_);
}

CUSTOMEGISTER(Tuple,TupleTest)