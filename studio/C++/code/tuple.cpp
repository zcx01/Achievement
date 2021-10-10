
#include "tuple.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <variant>

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

//运行时的索引
template <size_t n, typename ...T> 
constexpr std::variant<T...> _tuple_index(const std::tuple<T ...> &tpl,size_t i)
{
    if constexpr ( n > sizeof ...(T))
        throw std::out_of_range("out of range");
    
    if (i == n)
         return std::variant<T...>{ std::in_place_index<n>, std::get<n>(tpl) };
    
    return _tuple_index< (n <sizeof ...(T)-1 ? n+1:0) >(tpl,i);
}

template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}

template <typename T0, typename ... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) { 
    std::visit([&](auto && x){ s << x;}, v); 
    return s;
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

    std::tuple<std::string,double,double,int> t("123",4.5,6.7,8);
    COUT(std::get<std::string>(t))
    // COUT(std::get<double>(t)) // 非法, 引发编译期错误
    COUT(std::get<3>(t))

    int i=1;
    COUT(tuple_index(t,i))
    
    int i_count = std::tuple_size<decltype(t)>::value;
    COUT("元组的个数"<<i_count)
}

CUSTOMEGISTER(Tuple,TupleTest)