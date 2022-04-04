#include "algorithm.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

algorithmTest::algorithmTest(/* args */) 
{
    for(int i = 0; i < 98;i++)
        COUT(calAverageValue(0))
    for(int i = 0; i < 98;i++)
        COUT(calAverageValue(360))
    // COUT(calAverageValue(29))
}

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