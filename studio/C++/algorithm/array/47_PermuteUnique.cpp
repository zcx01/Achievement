#include "47_PermuteUnique.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> permuteUniqueChild(vector<vector<int>> &result,int n,vector<int> &nums)
{
    
}

vector<vector<int>> permuteUnique(vector<int> &nums)
{
    vector<vector<int>> result;
    int n = nums.size();
    if(n = 0) return result;
    vector<vector<int>> tmps;
    for (int i = 0; i < n; i++)
    {
        auto current = nums[i];
        vector<int> tmp;
        for(int j =0; j < tmps.size();j++)
        {
            for (int k = 0; k < tmps[j].size(); k++)
            {
                tmp.push_back(current);
                tmp.insert(tmp.end(), tmps[j].begin(), tmps[j].end());
                current = 
            }

        }
        
    }
}
//1

//1 2
//2 1

// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2
// 3 2 1

PermuteUnique::PermuteUnique(/* args */) 
{

}

CUSTOMEGISTER(PermuteUnique,PermuteUnique)