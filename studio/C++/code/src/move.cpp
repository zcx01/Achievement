#include "move.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

class  A
{
public:
    int *pointer;

    A():pointer(new int(1)){
        COUT("构造"<<" " << pointer)
    }

    A(A &a):pointer(new int(*a.pointer)){
        COUT("拷贝"<<" "<<pointer);
    }
    // 无意义的对象拷贝
    A(A &&a):pointer(a.pointer){
        a.pointer = nullptr;
        COUT("移动"<<" "<<pointer);
    }
    ~A(){
        COUT("析构"<<" "<<pointer);
        delete pointer;
    }
};

// 防止编译器优化
A return_rvalue(bool test)
{
    A a,b;
    if (test)
    {
        return a;// 等价于 static_cast<A&&>(a);
    }
    else
    {
        return b;//等价于 static_cast<A&&>(b);
    }
    
}

MoveTest::MoveTest(/* args */) 
{
    A obj = return_rvalue(false);
    COUT("obj")
    
    std::string str = "hello world";
    std::vector<std::string> v;

    // 将使用 push_back(const T&), 即产生拷贝行为
    v.push_back(str);   
    
    // 将输出 "Hello world"
    COUT(str); 

    // 将使用 push_back(const T&&), 不会出现拷贝行为
    // 而整个字符串会被移动到 vector 中，所以有时候 std::move 会用来减少拷贝出现的开销
    // 这步操作后, str 中的值会变为空
    v.push_back(std::move(str));

    // 将输出 "str: "
    std::cout << "str: " << str << std::endl;
}

CUSTOMEGISTER(Move,MoveTest)