#include "1790_AreAlmostEqual.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>

using namespace std;
//https://leetcode.cn/problems/check-if-one-string-swap-can-make-strings-equal/
//仅执行一次字符串交换能否使两个字符串相等
bool areAlmostEqual(string s1, string s2)
{
    if (s1 == s2)
        return true;
    int n = s1.size();
    int p = 0;
    int q = 0;
    //求长度为等于s1长度的一次交换的子串，如果其中有一个等于s2，就返回true
    while (p < n-1)
    {
        string tmp = s1;
        auto t = tmp[p];
        tmp[p] = tmp[q];
        tmp[q] = t;
        if (tmp == s2)
        {
            return true;
        }
        else
        {
            q++;
        }
        if (q == n)
        {
            q = p;
            p++;
        }
    }
    return false;
}
AreAlmostEqual::AreAlmostEqual(/* args */) 
{
    string s1 = "abcd", s2 = "dcba";
    COUT(areAlmostEqual(s1,s2));

}

CUSTOMEGISTER(AreAlmostEqual,AreAlmostEqual)