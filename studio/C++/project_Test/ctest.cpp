#include "ctest.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include "navi_roads_def.h"
//道路信息
struct RoadLaneInfo
{
    uint8_t front=0;
    uint8_t back=0;
    uint8_t frontEx=0;
    uint8_t backEx=0;
};

void write(std::vector<int> &data,int begin,int end,uint64_t value)
{   
    for (int i = end; i >= begin; i--)
    {
        data[i] = (value >> (8*(end-i))) & 0xFF;
    }
}

uint64_t read(std::vector<int> data,int begin,int end)
{
    uint64_t tmp=0;
    for (int i = end; i >= begin; i--)
    {
        tmp += data[i] << (8*(end-i));
    }
    return tmp;
}

ctestTest::ctestTest(/* args */) 
{
    RoadLaneInfo navi_road;
    navi_road.front = 255;
    navi_road.back = 11;
    uint32_t road_info_id = (navi_road.front << 24) + (navi_road.back << 16) + (navi_road.frontEx << 8) + navi_road.backEx;
    COUT(road_info_id)
    COUT(NaviRoadsIdEnum::NaviRoadsIdEnum_36)

    std::vector<int> data(10);
    uint64_t value = 999999.9*10;
    write(data,4,6,value);
    COUTI(data);
    value = read(data,4,6);
    COUT(value);
}



CUSTOMEGISTER(ctest,ctestTest)