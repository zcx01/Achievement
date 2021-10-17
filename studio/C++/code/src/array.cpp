#include "array.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <algorithm>

constexpr int Inc(int i) {

    return i + 1;

}
 void test( int size)
{
    // const int s1 = size;
    // constexpr int len = Inc(size);

    // std::array<int,len> arr1={};
    // for (size_t i = 0; i < size; i++)
    // {
       
    // }
    
}

void foo(int *p,int len)
{
    return;
}

ArrayTest::ArrayTest(/* args */) 
{
    std::array<int, 4> arr = {1, 2, 3, 4};
    COUT(arr.empty()); // 检查容器是否为空
    arr.size();  // 返回容纳的元素数

    COUTI(arr);

    std::sort(arr.begin(),arr.end(),[](int a,int b){return a > b;});
    
    COUTI(arr);

    test(10);

    //------------转化成C风格的接口
    // foo(arr,arr.size());//非法，无法隐式转化
    foo(&arr[0],arr.size());
    foo(arr.data(),arr.size());
}

CUSTOMEGISTER(Array,ArrayTest)