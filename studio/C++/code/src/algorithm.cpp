#include "algorithm.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <set>

using namespace std;

 // Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//是否有重复字符串
bool isUnique(string astr)
{
    for(int i =0; i <(int)astr.size();i++)
    {
        char c = astr.at(i);
        for(int j = 0; j < i; j++)
        {
            if(c == astr.at(j))
            {
                return false;
            }
        }
    }
    return true;
}

//字符串轮转 - s2可以通过s1转动得到
bool isFlipedString(string s1, string s2)
{
    if(s1.size() != s2.size())
    {
        return false;
    }
    auto s = s2 + s2;
    return s.find(s1) != std::string::npos;
}


//一次编辑
bool oneEditAway(string first, string second)
{
    int f_s = (int)first.size();
    int t_s = (int)second.size();
    if(abs(f_s-t_s) > 1)  return false;
    int count = 0;
    auto oneEditAwayP = [&](bool no_length,const string &f,const string &b)
    {
        for (int i = 0; i < (int)f.size(); i++)
        {
            int b_index = no_length ? i : i -count;
            if(b_index >= (int)b.size())
            {
                return true;
            }
            if (f.at(i) != b.at(b_index))
            {
                count++;
            }
            if (count > 1)
            {
                return false;
            }
        }
        return true;
    };
    //替换
    if (f_s == t_s)
    {
        return oneEditAwayP(true,first,second);
    }
    //删除
    else if(f_s > t_s)
    {
        return oneEditAwayP(false,first,second);
    }
    else
    {
        return oneEditAwayP(false,second,first);
    }
    return true;
}





algorithmTest::algorithmTest(/* args */) 
{
    COUT(oneEditAway("a",""))
}

//
float algorithmTest::calAverageValue(float speed) 
{
    speedSamp.push_back(speed);
    int speedCount = (int)speedSamp.size();
    if (speedCount < 18)
    {
        return speed;
    }
    else if (speedCount > 18)
    {
        speedSamp.erase(speedSamp.begin());
        speedCount--;
    }

    auto tempSpeed = speedSamp;
    std::sort(tempSpeed.begin(),tempSpeed.end());
    return std::accumulate(tempSpeed.begin()+1,tempSpeed.end()-1,0.0) / (speedCount-2);
}


CUSTOMEGISTER(algorithm,algorithmTest)