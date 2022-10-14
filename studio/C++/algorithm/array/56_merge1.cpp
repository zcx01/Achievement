#include "56_merge1.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//https://leetcode.cn/problems/merge-intervals/submissions/
//以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    vector<vector<int>> tmp;
    int n = intervals.size();
    if (n == 0 || n == 1) return intervals;
    int i = 0;
    std::sort(intervals.begin(), intervals.end(), [&](auto i, auto j)
              { return i[0] < j[0];});
    tmp.push_back(intervals[0]);
    while (i < n -1)
    {
        if (intervals[i + 1][0] > tmp.back()[1])
        {
            tmp.push_back(intervals[i+1]);
        }
        else if (tmp.back()[1] < intervals[i + 1][1])
        {
            tmp.back()[1] =  intervals[i+1][1];
        }
        ++i;
    }
    return tmp;
}

Merge1::Merge1(/* args */) 
{
    vector<vector<int>> intervals={{2,3},{4,5},{8,9},{1,10}};
    auto matrix = merge(intervals);
    COUT("---------输出-------------")
    for(auto ma : matrix)
        COUTI(ma);
}

CUSTOMEGISTER(Merge1,Merge1)