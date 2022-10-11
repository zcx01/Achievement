#include "807_advantage_count.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//二分查找
bool BinarySearch(vector<int> &nums1,int value)
{
     int startIndex = 0;
     int endIndex = nums1.size();
     while (true)
     {
         int currentIndex = (startIndex + endIndex) / 2;
         if (nums1[currentIndex] = value)
         {
            return true;
         }
         if (value < nums1[currentIndex])
         {
             endIndex = currentIndex;
         }
         else
         {
             startIndex = currentIndex;
         }
     }
     return false;
}

//https://leetcode.cn/problems/advantage-shuffle/
//优势洗牌
//返回 nums1 的任意排列，使其相对于 nums2 的优势最大化

vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size();
    std::sort(nums1.begin(),nums1.end());
    int beginIndex=0;
    std::vector<int> orderIndex;
    for(int i = 0; i < nums2.size(); i++)
    {
        orderIndex.push_back(i);
    }
    std::sort(orderIndex.begin(),orderIndex.end(),[&](int &i,int &j){return nums2[i] < nums2[j];});
    int b = 0 , e = n-1;
    for(auto value : nums1)
    {
        if(value > nums2[orderIndex[b]])
        {
            nums2[orderIndex[b++]] = value;
        }
        else
        {
            nums2[orderIndex[e--]] = value;
        }
    }
    return nums2;
}

AdvantageCount::AdvantageCount(/* args */) 
{
    vector<int> nums1={2,7,11,15};
    vector<int> nums2={1,10,4,11};
    auto num3 = advantageCount(nums1,nums2);
    COUTI(num3);

}

CUSTOMEGISTER(AdvantageCount,AdvantageCount)