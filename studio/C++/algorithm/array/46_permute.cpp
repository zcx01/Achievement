#include "46_permute.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>

using namespace std;
void permuteChild(vector<vector<int>> &result,vector<int> &nums,int f,int n)
{
    if(f == n)
    {
        result.emplace_back(nums);
        return;
    }
    for (int i = f; i < n; i++)
    {
        swap(nums[i],nums[f]);
        permuteChild(result, nums, f + 1, n);
        swap(nums[i], nums[f]);
    }
}

vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> result;
    permuteChild(result,nums,0,nums.size());
    return result;
}

Permute::Permute(/* args */) 
{
    vector<int> nums = {1, 2, 3};
    auto res = permute(nums);
    for(auto r : res)
    {
        COUTI(r);
    }
}

CUSTOMEGISTER(Permute,Permute)