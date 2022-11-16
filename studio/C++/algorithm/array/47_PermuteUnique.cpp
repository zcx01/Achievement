#include "47_PermuteUnique.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

void permuteUniqueChild(vector<vector<int>> &result,vector<int> &nums,set<int> &existence,int f,int n)
{
    if(f == n)
    {
        result.emplace_back(nums);
        return;
    }
    for (int i = f; i < n; i++)
    {   
        if(existence.count(nums[f]) == 0)
        {
            swap(nums[i], nums[f]);
        }
        else
        {
            continue;
        }
        permuteUniqueChild(result, nums,existence, f + 1, n);
        if (f == 0)
        {
            existence.insert(nums[f]);
        }
        COUTI(existence);
        swap(nums[i],nums[f]);
    }
}

vector<vector<int>> permuteUnique(vector<int> &nums)
{
    vector<vector<int>> result;
    set<int> existence;
    permuteUniqueChild(result,nums,existence,0,nums.size());
    return result;
}

PermuteUnique::PermuteUnique(/* args */) 
{
    vector<int> nums = {1, 1, 2};
    auto res = permuteUnique(nums);
    // for(auto r : res)
    // {
    //     COUTI(r);
    // }
}

CUSTOMEGISTER(PermuteUnique,PermuteUnique)